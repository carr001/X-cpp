﻿#include "XFtpServerCMD.h"

#include <event2/bufferevent.h>
#include <event2/event.h>
#include <string.h>

#include <iostream>
using namespace std;
void EventCB(struct bufferevent *bev, short what, void *arg) {
    XFtpServerCMD *cmd = (XFtpServerCMD *)arg;

    // 如果对方网络断掉，或者机器死机有可能收不到BEV_EVENT_EOF数据
    if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT)) {
        cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT" << endl;
        bufferevent_free(bev);
        delete cmd;
    }
}
// 子线程XThread  event事件分发
static void ReadCB(bufferevent *bev, void *arg) {
    XFtpServerCMD *cmd = (XFtpServerCMD *)arg;
    char data[1024] = {0};
    for (;;) {
        int len = bufferevent_read(bev, data, sizeof(data) - 1);
        if (len <= 0) break;
        data[len] = '\0';
        cout << data << flush;

        // 测试代码，要清理掉
        if (strstr(data, "quit")) {
            bufferevent_free(bev);
            delete cmd;
            break;
        }
    }
}
// 初始化任务 运行在子线程中
// 功能：专门用来接收 ftp 命令的，用 bufferevent 来做
// 子线程分发的 Main 函数中会调用

bool XFtpServerCMD::Init() {
    cout << "XFtpServerCMD::Init()" << endl;
    // 监听socket bufferevent
    // base socket
    bufferevent *bev =
        bufferevent_socket_new(base, sock, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, ReadCB, 0, EventCB, this);
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    // 添加超时
    timeval rt = {10, 0};
    bufferevent_set_timeouts(bev, &rt, 0);
    return true;
}

XFtpServerCMD::XFtpServerCMD() {}

XFtpServerCMD::~XFtpServerCMD() {}

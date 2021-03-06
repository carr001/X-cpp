//#include <afxwin.h>
//#include <stdio.h>
//
//#include <iostream>
//using namespace std;
//
//class Singleton {
//private:
//    Singleton() {
//        m_singer = NULL;
//        cout << "构造一个Singleton对象" << endl;
//    }
//
//public:
//    static Singleton* getInstance() {  //懒汉式:延迟加载
//        if (m_singer == NULL) {
//            m_singer = new Singleton;
//        }
//        return m_singer;
//    }
//
//private:
//    static Singleton* m_singer;
//};
//
//UINT Func(LPVOID) {
//    printf("%x\n", Singleton::getInstance());
//    return 0;
//}
//Singleton* Singleton::m_singer =
//NULL;  // new Singleton; 在C++中构造函数不是线程安全的
//
//
//int main(void) {
//    for (int i = 0; i < 10; i++) {
//        AfxBeginThread(Func, NULL);
//    }
//    system("pause");
//    return 0;
//}

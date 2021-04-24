#pragma once
// �����ü����������

class UseCount {
public:
    UseCount() { count = new int(1); }
    UseCount(const UseCount& other) : count(other.count) { ++* count; }
    ~UseCount() {
        if (--*count == 0) {
            delete count;
        }
    }
    bool IsOnly() { return *count==1; }
    UseCount& operator= (const UseCount& other) {
        ++(*other.count);
        if (--(*count)==0) {
            delete count;
            count = other.count;
            return *this;
        }
        count = other.count;
        return *this;
    }

    // Ϊ����࿽�����캯������
    // ����:�������첢���ؽ��,other����+1�����������-1
    bool ReAttach(const UseCount& other) {
        ++(*count);
        if (--(*count)==0) {
            delete count;
            count = other.count;
            return true;
        }
        count = other.count;
        return false;
    }
private:
    int* count;
};

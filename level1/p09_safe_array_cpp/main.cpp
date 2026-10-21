#include <iostream>
using namespace std;

template <typename T>
class SafeArray {
private:
    T* data;
    int capacity;

public:
    SafeArray(int size) {
        capacity = size;
        data = new T[capacity];
    }

    ~SafeArray() {
        delete[] data;
    }
    T& operator[](int index) {
        if (index < 0 || index >= capacity) {
            cout << "报错：数组下标越界！" << endl;
            return data[0]; 
        }
        return data[index];
    }
};

int main() {
    
    SafeArray<int> arr(5);

    arr[0] = 10;
    arr[4] = 50;
    cout << "arr[0] = " << arr[0] << endl;

   
    cout << "尝试访问 arr[10]..." << endl;
    arr[10] = 99; // 这里会触发打印 "报错：数组下标越界！"

    return 0;
}

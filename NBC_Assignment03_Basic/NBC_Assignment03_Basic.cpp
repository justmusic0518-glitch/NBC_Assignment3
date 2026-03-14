#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Inventory{
    T* pItems_ = new T[];
    int capacity_;
    int size_;

public:
    Inventory(int capacity = 10) : capacity_(capacity){
        if (capacity < 1)
            capacity_ = 1;
        new T[capacity_];
    }

    ~Inventory(){
        delete[] pItems_;
        pItems_ = nullptr;
    }

    void AddItem(const T& item) // 수정하지는 마 근데 참조할꺼야
    {
        if (capacity_ > size_)
        {
            pItems_[size_] = item;
            ++size_;
        }
        else if (capacity_ == size_)
            cout << "인벤토리가 꽉 찼습니다!\n";
    }
    const void PrintAllItems(){
        for (int i = 0; i < size_ - 1; ++i)
        {
            pItems_[i].PrintInfo();
        }
    }

    void RemoveLastItem(){
        if (size_ == 0) { cout << "인벤토리가 비어있습니다.\n"; }
        else { --size_; }
    }

    int GetSize() const{ return size_; }
    int GetCapacity() const{ return capacity_; }
};

class Item{
    string name_;
    int price_;
public:
    Item(string name, int price) : name_(name), price_(price){}
    void PrintInfo() const {
        cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
    }
};

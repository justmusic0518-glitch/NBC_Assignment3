#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Item{
    string name_;
    int price_;
public:
    Item(){}
    Item(string name, int price) : name_(name), price_(price){}
    void PrintInfo() const {
        cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
    }
    
    string GetName(){
        return name_;
    }
    int Getprice(){
        return price_;
    }
    
    string SetName(string name){
        name_ = name;
    }
    int Setprice(int price){
        price_ = price;
    }
}; 

bool compareItemsByPrice(Item& a, Item& b){
    return a.Getprice() < b.Getprice();
}

template <typename T>
class Inventory{
    T* pItems_;
    int capacity_;
    int size_;

public:
    Inventory(int capacity = 10) : capacity_(capacity){
        if (capacity < 1)
            capacity_ = 1;
        else
            pItems_ = new T[capacity_];
    }
    Inventory(const Inventory<T>& other){
        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; ++i)
        {
            pItems_[i] = other.pItems_[i];
        }
        cout << "인벤토리 복사 완료" << endl;
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
        {
            Resize(capacity_ * 2);
            pItems_[size_] = item;
            ++size_;
            cout << "인벤토리 용량 * 2\n";
        }
    }
    const void PrintAllItems(){
        for (int i = 0; i <= size_ - 1; ++i)
        {
            pItems_[i].PrintInfo();
        }
    }
    void Assign(const Inventory<T>& other){
        delete[] pItems_;
        pItems_ = nullptr;
        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_];
        for (int i = 0; i < size_; ++i)
        {
            pItems_[i] = other.pItems_[i];
        }
    }
    void Resize(int newCapacity){
        T* pNewItems_ = new T[newCapacity];  // 포인터를 써서 할당된 값에 주소 불러줌
        for (int i = 0; i < size_; ++i)
        {
            pNewItems_[i] = pItems_[i];
        }
        delete[] pItems_;
        capacity_ = newCapacity; 
        pItems_ = pNewItems_;
    }

    void RemoveLastItem(){ 
        if (size_ == 0) { cout << "인벤토리가 비어있습니다.\n"; }
        else { --size_; }
    }
    
    void SourItems(){
        sort(pItems_, pItems_+size_, compareItemsByPrice);
    }

    int GetSize() const{ return size_; }
    int GetCapacity() const{ return capacity_; }
};

int main(){
    Inventory<Item> inven(3);
    Item sword("대검", 5000);
    Item Bow("활", 6000);
    Item knife("단검", 3000);
    Item staff("지팡이", 5000);
    
    inven.AddItem(sword);
    inven.AddItem(Bow);
    inven.AddItem(knife);
    inven.PrintAllItems(); // PrintAllItems 확인
    
    inven.AddItem(staff); // Add 확인
    cout << "inven의 capacity : " << inven.GetCapacity() << "\n";

    Inventory<Item> inven2;
    inven2.Assign(inven);
    cout << "inven2======== 복사 확인\n";
    inven2.PrintAllItems();
    
    inven2.Resize(4);
    cout << "inven의 capacity : " << inven2.GetCapacity() << "\n";
    
    inven2.RemoveLastItem(); // 아이템 지우기
    inven2.PrintAllItems();
    cout << "inven 정렬 " << inven2.GetCapacity() << "\n";
    inven2.SourItems();
    inven2.PrintAllItems();
}

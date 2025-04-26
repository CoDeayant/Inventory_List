#include <iostream>
#include <fstream>
#include <vector> //Здесь нужен для того,чтобы хранить 2 индекса, Индекс Элемента - его имя и Количество Предмета.

using namespace std;

class InventoryData
{
    private:
        int index_name; //Название объекта
        int count; // Количество объектов одного типа
        InventoryData* next; // Чтобы переходить из одного объекта одного типа в другой
    public:
        
        InventoryData(int n = 0, int c = 0, InventoryData* ptr = nullptr)
            : index_name(n),count(c),next(ptr) {};
        
        ~InventoryData() {};

        friend class InventoryHandle;
};

class InventoryHandle
{
    private:
        InventoryData* head;
        InventoryData* get_last();
        InventoryData* get_elem(int index);
    public:
        InventoryHandle();
        ~InventoryHandle();

        void push_front(int index_name,int val); //Если мы переставляем элементы(предметы), то вот это используем, чтобы поставить в начало

        void push_any(int index_name, int val, int index); //Куда мы выберем, туда и ставим

        void push_back(int index_name, int val); //Это для конца

        void write(ostream& out); //Вставляем предметы в инвентарь

        void read(ifstream& in); //Берем прдеметы снаружи
};

InventoryHandle::InventoryHandle()
{
    head = nullptr;
}

InventoryHandle::~InventoryHandle()
{
    InventoryData* ptr = head;
    while(ptr -> next)
    {
        ptr = head;
        head = head -> next;
        delete(ptr);
    }
    head = nullptr;
}

InventoryData* InventoryHandle::get_last()
{
    InventoryData* ptr = head;
    if(ptr)
    {
        while (ptr -> next)
        {
            ptr = ptr -> next;
        }
    }
    return (ptr);
}

InventoryData* InventoryHandle::get_elem(int i)
{
    InventoryData* ptr = head;
    if(ptr)
    {
        while (--i) 
        {
            ptr = ptr -> next;
        }
    }
    return(ptr);
}


void InventoryHandle::push_front(int index_name, int val)
{
    head = new InventoryData(index_name,val);
}

void InventoryHandle::push_back(int index_name, int val)
{
    if(!head)
    {
        head = new InventoryData(index_name,val);
    }
    if(head)
    {
        InventoryData* ptr = get_last();
        ptr -> next = new InventoryData(index_name,val);
    }
}

void InventoryHandle::read(ifstream& in)
{
    int val = 0;
    int index_name = 0;
    while(in >> val)
    {
        push_back(index_name,val);
    }
}   

int main()
{
    ifstream file_in;
    ofstream file_out;

    file_in.open("input.txt");
    file_out.open("output.txt");

    file_in.close();
    file_out.close();
    return 0;
}
#include <iostream>
#include <fstream>
using namespace std;

// Структура для Двусвязного списка
struct Node 
{
    int data;       // Значение, которое хранится в узле
    Node* prev;     // Указатель на прошлый узел
    Node* next;     // Указатель на следующий узел
};

// Функция для создания нового узла
Node* createNode(int value) 
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

// Функция для вставки узла в конец списка
void insertEnd(Node*& head, int value)
{
    Node* newNode = createNode(value);
    if (!head) 
    {
        head = newNode;
    } 
    else 
    {
        Node* temp = head;
        while (temp->next) 
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Swap функция 
void swapData(Node* a, Node* b) 
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Сортировка пузырьком для двусвязного списка
void bubbleSort(Node* head) 
{
    //Это если у нас пустой список или список с 1 элементом
    if (!head || !head->next) 
    {
        return;
    }

    bool swapped;
    do 
    {
        swapped = false;
        Node* current = head;
        while (current->next) 
        {
            if (current->data > current->next->data) 
            {
                swapData(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
    } 
    while (swapped);
}

// Функция для разделения списка на две половины
void split(Node* source, Node*& left, Node*& right) 
{
    //Это если у нас пустой список или список с 1 элементом
    if (!source || !source->next) 
    {
        left = source;
        right = nullptr;
        return;
    }

    Node* slow = source;
    Node* fast = source->next;

    while (fast) 
    {
        fast = fast->next;
        if (fast) 
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    left = source;           // Левая половина начнется с Головы(начала) изначального списка
    right = slow->next;      // Правая половина начнется с середины изначального списка (slow->next)
    slow->next = nullptr;    // Разделим половины и установим slow->next на nullptr.
    if (right)               // Если правая половина существует, то поставим prev на nullptr.
    {
        right->prev = nullptr;
    }   
}

// Функция для слияния двух отсортированных списков
Node* merge(Node* left, Node* right) 
{
    //Проверки ,если у нас не получились половины (Например список с 1 элементом или пустой список)
    if (!left)
    { 
        return right;
    }

    if (!right) 
    {
        return left;
    }

    Node head;
    Node* tail = &head;
    head.next = nullptr;

    //Проверим обе половины
    while (left && right) 
    {
        //Это если элемент левой половины меньше либо равен ,чем элемент второй половины
        if (left->data <= right->data) 
        {
            tail->next = left;
            left->prev = tail;
            left = left->next;
        } 
        //А это если наоборот элемент правой половины меньше либо равен ,чем элемент левой половины
        else 
        {
            tail->next = right;
            right->prev = tail;
            right = right->next;
        }
        tail = tail->next;
    }
    //Ну случай, если в одной половине был один лишний элемент, его записываем в конец
    if (left) 
    {
        tail->next = left;
        left->prev = tail;
    }
    if (right) 
    {
        tail->next = right;
        right->prev = tail;
    }

    //Теперь в новом отсортированном массиве мы укажем ,что prev элемент новой головы равен nullptr, для избежания цикла
    Node* newHead = head.next;
    if (newHead)   
    {
        newHead->prev = nullptr;
    }
    return newHead;
}

// Сортировка слиянием для двусвязного списка
Node* mergeSort(Node* head) 
{
    //Это если у нас пустой список или список с 1 элементом
    if (!head || !head->next) 
    {
        return head;
    }

    Node* left;
    Node* right;
    split(head, left, right);

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

// Функция для записи списка в файл
void writeListToFile(Node* head, const char* filename) 
{
    //Откроем файл для записи данных
    ofstream file_out(filename);
    if (!file_out.is_open()) 
    {
        cerr << "Ошибка: Не удалось открыть файл для записи!" << endl;
        return;
    }

    // Подсчитаем количество элементов в списке
    int count = 0;
    Node* temp = head;
    while (temp) 
    {
        count++;
        temp = temp->next;
    }

    // Записываем количество и отсортированный список в файл
    file_out << count << " ";
    temp = head;
    while (temp) 
    {
        file_out << temp->data << " ";
        temp = temp->next;
    }

    file_out.close();
}

int main() {
    Node* head = nullptr;

    // Откроем файл
    ifstream file_in("input.txt");
    if (!file_in.is_open()) 
    {
        cerr << "Ошибка: Не удалось открыть входной файл!" << endl;
        return 1;
    }

    int sortKey, value;
    bool Go_next = true; // Проверим файл, чтобы он не содержал неправильных данных

    // Ключ сортировки, есть ли он, если его нет ,значит файл пустой
    if (!(file_in >> sortKey)) 
    {
        cerr << "Ошибка: Файл пуст или не содержит ключа сортировки!" << endl;
        file_in.close();
        return 1;
    }

    // Проверим, 0 или 1 для ключа сортировки в файле
    if (sortKey != 0 && sortKey != 1) 
    {
        cerr << "Ошибка: Неверный ключ сортировки! Ключ должен быть 0 или 1." << endl;
        file_in.close();
        return 1;
    }

    // Читаем чисел из файла
    while (file_in >> value) { 
        // Проверим следующий символ 
        if (file_in.peek() != EOF && !isspace(file_in.peek())) 
        {
            cerr << "Ошибка: Обнаружены недопустимые символы в файле!" << endl;
            Go_next = false;
            file_in.close();
            return 1;
        }
        insertEnd(head, value);
    }

    // Проверка на то , остались ли непрочитанные символов в файле
    if (!file_in.eof()) 
    {
        cerr << "Ошибка: Обнаружены недопустимые символы в файле!" << endl;
        file_in.close();
        return 1;
    }

    file_in.close();

    // Если неправильные данные в файле, прерываем программу
    if (Go_next) 
    {
        // Для Merge Sort
        if (sortKey == 0) 
        {
            cout << "Используется сортировка слиянием (Merge Sort)." << endl;
            head = mergeSort(head); 
        } 
        //Для Bubble Sort
        else if (sortKey == 1) 
        {
            cout << "Используется сортировка пузырьком (Bubble Sort)." << endl;
            bubbleSort(head); 
        }

        // Запишем все, что мы прочитали в файл
        writeListToFile(head, "output.txt");
    }

    // Очистим память
    while (head) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    cout << "Список успешно отсортирован и сохранен в файл 'output.txt'." << endl;
    return 0;
}

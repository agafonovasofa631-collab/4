#include <iostream>

using namespace std;


// 1. Односвязный список
template <typename T>
class SinglyLinkedList {
private:
    // Структура узла: хранит данные и указатель только на следующий элемент
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head; // Указатель на первый элемент
    Node* tail; // Указатель на последний элемент (для быстрого добавления)
    int count;  // Количество элементов в списке

public:
    // Итератор для односвязного списка 
    class Iterator {
    private:
        Node* current; // Внутри итератора храним указатель на текущий узел
    public:
        Iterator(Node* node) : current(node) {}

        // Разыменование: получаем ссылку на данные внутри узла
        T& operator*() { return current->data; }

        // Оператор ++: переходим к следующему узлу
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Сравнение: нужно для остановки цикла (сравниваем с end())
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    // Конструктор и деструктор
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~SinglyLinkedList() { clear(); } // При удалении списка обязательно чистим память

    // Добавление элемента в конец (O(1), так как есть tail)
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            // Если список пуст, новый узел становится и головой, и хвостом
            head = tail = newNode;
        }
        else {
            // Иначе привязываем его к хвосту
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    // Вывод элементов
    void print() const {
        Node* current = head;
        cout << "[ ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "]\n";
    }

    // Очистка памяти (проходим по всем узлам и удаляем их)
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    // Методы возврата итераторов для цикла for
    Iterator begin() { return Iterator(head); }      // Начало списка
    Iterator end() { return Iterator(nullptr); }     // Конец (nullptr)
};


// Двусвязный список
template <typename T>
class DoublyLinkedList {
private:
    // Структура узла: хранит данные и указатели на следующий и предыдущий элементы
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    // Итератор для двусвязного списка
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() { return current->data; }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinkedList() { clear(); }

    // Добавление элемента в конец
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            // Связываем старый хвост с новым узлом (в обе стороны)
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    void print() const {
        Node* current = head;
        cout << "[ ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "]\n";
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    // Методы возврата итераторов
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};


int main() {
    setlocale(LC_ALL, "ru");

    cout << "=== Тестирование SinglyLinkedList ===\n";
    SinglyLinkedList<int> singleList;
    singleList.push_back(10);
    singleList.push_back(20);
    singleList.push_back(30);

    // Вывод обычным методом
    cout << "Вывод через метод print(): ";
    singleList.print();

    // Вывод с помощью итератора (range-based for)
    // Это работает благодаря методам begin() и end() в классе
    cout << "Вывод через итератор (range-based for): ";
    for (int val : singleList) {
        cout << val << " ";
    }
    cout << "\n\n";

    cout << "=== Тестирование DoublyLinkedList ===\n";
    DoublyLinkedList<string> doubleList;
    doubleList.push_back("Apple");
    doubleList.push_back("Banana");
    doubleList.push_back("Cherry");

    cout << "Вывод через метод print(): ";
    doubleList.print();

    cout << "Вывод через итератор (range-based for): ";
    for (auto val : doubleList) {
        cout << val << " ";
    }
    cout << "\n";

    return 0;
}
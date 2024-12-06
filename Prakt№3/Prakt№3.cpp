// Prakt№3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>


struct Node {
    int data;          // Данные, которые хранит узел (в данном случае, целое число).
    Node* prev;        // Указатель на предыдущий узел в списке.  Значение nullptr, если это первый узел.
    Node* next;        // Указатель на следующий узел в списке.  Значение nullptr, если это последний узел.
    Node(int data) : data(data), prev(nullptr), next(nullptr) {}
    // Конструктор для узла.  Инициализирует поле `data` переданным значением, а указатели `prev` и `next` устанавливаются в `nullptr` (нулевые указатели, указывающие ни на что).
};

class DoublyLinkedList {
private:
    Node* head; // Указатель на первый узел списка.  Инициализируется как nullptr в конструкторе.
    Node* tail; // Указатель на последний узел списка. Инициализируется как nullptr в конструкторе.

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    // Конструктор класса. Создает пустой список, устанавливая указатели head и tail в nullptr.

    void push_front(int data) { // Добавляет новый элемент в начало списка.
        Node* newNode = new Node(data); // Создаем новый узел с заданными данными.
        if (head == nullptr) {          // Если список пустой (head == nullptr)
            head = tail = newNode;      // Новый узел становится одновременно и головой, и хвостом списка.
        }
        else {
            newNode->next = head;       // Устанавливаем указатель next нового узла на текущую голову списка.
            head->prev = newNode;       // Устанавливаем указатель prev текущей головы списка на новый узел.
            head = newNode;             // Новый узел становится новой головой списка.
        }
    }

    void push_back(int data) { // Добавляет новый элемент в конец списка.
        // Создаем новый узел
        Node* newNode = new Node(data);

        // Если список пуст, новый узел становится головой и хвостом
        if (tail == nullptr) {
            head = tail = newNode;
            return; // Выходим из функции, так как всё сделано
        }

        // Если список не пуст, то новый узел добавляется в конец
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode; // Обновляем хвост списка
    }

    // Удаление элемента из начала списка
    void pop_front() {
        if (head == nullptr) return; // Список пуст, ничего удалять не нужно

        Node* temp = head; // Сохраняем указатель на удаляемый узел

        if (head == tail) { // Если в списке только один узел
            head = tail = nullptr; // Список становится пустым
        }
        else {
            head = head->next; // Перемещаем указатель head на следующий узел
            head->prev = nullptr; // Обновляем указатель prev новой головы списка
        }
        delete temp; // Удаляем узел из памяти
    }

    // Удаление элемента из конца списка
    void pop_back() {
        if (tail == nullptr) return; // Список пуст, ничего удалять не нужно

        Node* temp = tail; // Сохраняем указатель на удаляемый узел

        if (head == tail) { // Если в списке только один узел
            head = tail = nullptr; // Список становится пустым
        }
        else {
            tail = tail->prev; // Перемещаем указатель tail на предыдущий узел
            tail->next = nullptr; // Обновляем указатель next нового хвоста списка
        }
        delete temp; // Удаляем узел из памяти
    }

    // Вывод всех элементов списка на экран
    void display() {
        Node* current = head; // Начинаем с первого узла (head)
        while (current != nullptr) { // Проходим по списку пока не достигнем конца (nullptr)
            std::cout << current->data << " "; // Выводим данные текущего узла
        current = current->next; // Переходим к следующему узлу
        }
        std::cout << std::endl;
    }

    // Сортировка списка методом пузырька
    void sort() {
        if (head == nullptr || head == tail) return; // Если список пуст или содержит один элемент - сортировать нечего

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr; // Указатель на последний просмотренный узел

        do {
            swapped = false;
            ptr1 = head;
            while (ptr1->next != lptr) {
                if (ptr1->data > ptr1->next->data) {
                    std::swap(ptr1->data, ptr1->next->data); // Меняем местами значения данных в узлах
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped); // Повторяем, пока не будет сделано ни одной перестановки
    }

    // Удаление дубликатов из списка
    void removeDuplicates() {
        if (head == nullptr) return; // Пустой список - ничего удалять

        Node* current = head;
        while (current != nullptr) {
            Node* runner = current; // runner начинает с текущего элемента
            while (runner->next != nullptr) {
                if (runner->next->data == current->data) { // Дубликат найден
                    Node* temp = runner->next; // Сохраняем указатель на дубликат
                    runner->next = temp->next; // "Пропускаем" дубликат
                    delete temp;              // Удаляем дубликат
                }
                else {
                    runner = runner->next;    // Переходим к следующему элементу
                }
            }
            current = current->next; // Переходим к следующему элементу
        }
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    DoublyLinkedList list;
    int choice, value;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить элемент в начало\n";
        std::cout << "2. Добавить элемент в конец\n";
        std::cout << "3. Удалить элемент с начала\n";
        std::cout << "4. Удалить элемент с конца\n";
        std::cout << "5. Отобразить список\n";
        std::cout << "6. Сортировать список\n";
        std::cout << "7. Удалить дубликаты\n";
        std::cout << "0. Выйти\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите значение: ";
            std::cin >> value;
            list.push_front(value);
            break;
        case 2:
            std::cout << "Введите значение: ";
            std::cin >> value;
            list.push_back(value);
            break;
        case 3:
            list.pop_front();
            break;
        case 4:
            list.pop_back();
            break;
        case 5:
            std::cout << "Список :\n";
            list.display();
            break;
        case 6:
            list.sort();
            break;
        case 7:
            list.removeDuplicates();
            break;
        case 0:
            std::cout << "Выход...\n";
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
        std::cout << "\n\n\n\n";
    } while (choice != 0);

    return 0;
}
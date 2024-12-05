#include <iostream>

using namespace std;

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node *head;
    Node *tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void addFirst(const T &element) {
        Node *newNode = new Node(element);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void addLast(const T &element) {
        Node *newNode = nullptr;
        try {
            newNode = new Node(element); // Attempt to allocate memory
        } catch (const std::bad_alloc &e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            return; // Exit the function or handle the error
        }

        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }


    void addAt(const T &element, int index) {
        if (index < 0 || index > size) {
            cout << "Index out of bounds." << endl;
            return;
        }

        if (index == 0) {
            addFirst(element);
        } else if (index == size) {
            addLast(element);
        } else {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            Node *newNode = new Node(element);
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            size++;
        }
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds." << endl;
            return;
        }

        Node *temp;
        if (index == 0) {
            temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (index == size - 1) {
            temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        size--;
    }

    void displayForward() {
        if (!head) {
            cout << "The list is empty." << endl;
            return;
        }

        Node *temp = head;
        int ctr = 1;
        while (temp) {
            cout << ctr << " - " << temp->data << endl;
            temp = temp->next;
            ctr++;
        }
        cout << endl;
    }

    int search(const string &element) {
        Node *temp = head;
        int ctr = 0;
        while (temp) {
            if (temp->data == element) {
                return ctr;
            }
            ctr++;
            temp = temp->next;
        }
        return -1;
    }


    void displayBackward() {
        if (!tail) {
            cout << "The list is empty." << endl;
            return;
        }

        int ctr = 1;
        Node *temp = tail;
        while (temp) {
            cout << ctr << " - " << temp->data << endl;
            temp = temp->prev;
            ctr++;
        }
        cout << endl;
    }

    void clear() {
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;

    }

    int getSize() const {
        return size;
    }

    T getAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index is out of range");
        }
        Node *current;
        current = head;
        for (int i = 0; i <index ; ++i) {
            current = current->next;
        }
        return current->data;
    }

    Node *getHead() const {
        return head;
    }
};

//
// Created by 김령교 on 7/9/23.
//

#ifndef CPPAI_LINKEDLIST_H
#define CPPAI_LINKEDLIST_H

#include <vector>
#include <string>

using namespace std;

// LinkedList Node 정의
template <class T>
class LinkedListNode {
public:
    T data;
    LinkedListNode* next;

    explicit LinkedListNode(T data) : data(data) {
        next = nullptr;
    }
};

template <class T>
class LinkedListIterator {
private:
    LinkedListNode<T>* current;

public:
    LinkedListIterator(LinkedListNode<T>* node) : current(node) {}

    LinkedListIterator<T>& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }

    T& operator*() const {
        return current->data;
    }

    bool operator==(const LinkedListIterator<T>& other) const {
        return current == other.current;
    }

    bool operator!=(const LinkedListIterator<T>& other) const {
        return current != other.current;
    }
};

// LinkedList 클래스 정의
template <class T>
class LinkedList {
private:
    LinkedListNode<T>* head;
    int count;

public:
    LinkedList();
    ~LinkedList();

    int size();
    LinkedListNode<T>* first();
    void add(T item);
    T get(int index);
    LinkedList<T>* search(string keyword);
    bool update(int index, T updatedSong);
    bool update(T item, T updatedSong);
    bool remove(int index);
    bool remove(T item);

    LinkedListIterator<T> begin() {
        return LinkedListIterator<T>(head);
    }

    LinkedListIterator<T> end() {
        return LinkedListIterator<T>(nullptr);
    }
};

template <class T>
LinkedList<T>::LinkedList() {
    count = 0;
    head = nullptr;
}

template <class T>
LinkedList<T>::~LinkedList() {
    LinkedListNode<T>* current = head;
    while (current != nullptr) {
        LinkedListNode<T>* next = current->next;
        delete current;
        current = next;
    }
}

template <class T>
int LinkedList<T>::size() {
    return count;
}

template <class T>
LinkedListNode<T>* LinkedList<T>::first() {
    return head;
}

template <class T>
void LinkedList<T>::add(T item) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(item);
    if (head == nullptr) {
        head = newNode;
    } else {
        LinkedListNode<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    count++;
}

template <class T>
T LinkedList<T>::get(int index) {
    LinkedListNode<T>* temp = head;
    int currentIndex = 0;
    while (temp != nullptr && currentIndex < index) {
        temp = temp->next;
        currentIndex++;
    }

    if (temp != nullptr) {
        return temp->data;
    } else {
        // 인덱스가 범위를 벗어난 경우 예외 처리 또는 기본값 반환 등을 수행할 수 있습니다.
        throw out_of_range("Index out of range");
    }
}

template <class T>
LinkedList<T>* LinkedList<T>::search(string keyword) {
    LinkedList<T>* result = new LinkedList<T>();
    LinkedListNode<T>* temp = head;
    while (temp != nullptr) {
        if (temp->data == keyword) {
            result->add(temp->data);
        }
        temp = temp->next;
    }
    return result;
}

template <class T>
bool LinkedList<T>::update(int index, T updatedSong) {
    LinkedListNode<T>* temp = head;
    int currentIndex = 0;
    while (temp != nullptr && currentIndex < index) {
        temp = temp->next;
        currentIndex++;
    }

    if (temp != nullptr) {
        temp->data = updatedSong;
        return true;
    } else {
        return false;
    }
}

template <class T>
bool LinkedList<T>::update(T item, T updatedSong) {
    LinkedListNode<T>* temp = head;
    while (temp != nullptr && temp->data != item) {
        temp = temp->next;
    }
    if (temp != nullptr) {
        temp->data = updatedSong;
        return true;
    } else {
        return false;
    }
}


template <class T>
bool LinkedList<T>::remove(int index) {
    LinkedListNode<T>* temp = head;
    LinkedListNode<T>* prev = nullptr;
    int currentIndex = 0;
    while (temp != nullptr && currentIndex < index) {
        prev = temp;
        temp = temp->next;
        currentIndex++;
    }
    if (temp != nullptr) {
        if (prev != nullptr) {
            prev->next = temp->next;
        } else {
            head = temp->next;
        }
        delete temp;
        count--;
        return true;
    } else {
        return false;
    }
}

template <class T>
bool LinkedList<T>::remove(T item) {
    LinkedListNode<T>* temp = head;
    LinkedListNode<T>* prev = nullptr;
    while (temp != nullptr && temp->data != item) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != nullptr) {
        if (prev != nullptr) {
            prev->next = temp->next;
        } else {
            head = temp->next;
        }
        delete temp;
        count--;
        return true;
    } else {
        return false;
    }
}

#endif //CPPAI_LINKEDLIST_H

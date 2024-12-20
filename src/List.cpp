#include "List.h"
#include "Router.h"

template<typename T>
List<T>::List() : head(nullptr) {
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::addNode(const T &node) {
    auto *newNode = new Node<T>{node, head};
    head = newNode;
}

template<typename T>
void List<T>::removeNode(const T &node) {
    Node<T> *current = head;
    Node<T> *prev = nullptr;
    while (current != nullptr && current->data != node) {
        prev = current;
        current = current->next;
    }
    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        delete current;
    }
}

template<typename T>
void List<T>::clear() {
    while (head != nullptr) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

template class List<Router>;

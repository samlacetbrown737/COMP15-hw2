/*
 *  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  LinkedList.h
 *
 *  PURPOSE
 *
 *  Modified By:
 *           On:
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//typedef char E;

// Do a char version first, then save your work,
// then convert the code to use templates, and uncomment the template
// line.
template<typename E>
class LinkedList
{
	public:
        LinkedList();
        LinkedList(E element);
        LinkedList(E elements[], int len);
        LinkedList(const LinkedList &other);

        ~LinkedList();
        LinkedList &operator=(const LinkedList &rhs);

        bool isEmpty();
        void clear();
        int size();
        E first();
        E last();
        E elementAt(int index);
        void print();
        void pushAtBack(E elem);
        void pushAtFront(E elem);
        void insertAt(E elem, int index);
        void insertInOrder(E elem);
        void popFromFront();
        void popFromBack();
        void removeAt(int index);
        void replaceAt(E elem, int index);
        void concatenate(LinkedList &second);
        void shrink();
        bool find(E elem);

    private:
        struct Node {
            E info;
            Node* next;
            Node* prev;
        };
        int length;
        Node* front;
        Node* back;
        Node* curr_pos;
};


#include <iostream>
#include <sstream>
#include "LinkedList.h"

using namespace std;

// Default constructor
// template<class E>
// LinkedList<T>::LinkedList()

template<typename E>
LinkedList<E>::LinkedList()
{
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
    back = nullptr;
}

template<typename E>
LinkedList<E>::LinkedList(E elem) {
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
    back = nullptr;
    length   = 1;
    Node *node = new Node;
    node->info = elem;
    front    = node;
    curr_pos = node;
    back = node;
}

template<typename E>
LinkedList<E>::LinkedList(E elems[], int len) {
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
    back = nullptr;
    for(int i = 0; i < len; i++) {
        pushAtBack(elems[i]);
    }
}

template<typename E>
LinkedList<E>::LinkedList(const LinkedList<E> &other) {
    length   = other.length;
    front    = other.front;
    curr_pos = front;
    back = other.back;
}

template<typename E>
LinkedList<E>::~LinkedList() {
    curr_pos = front;
    while(curr_pos) {
        Node* next = curr_pos->next;
        delete curr_pos;
        curr_pos = next;
    }
}

template<typename E>
LinkedList<E> &LinkedList<E>::operator=(const LinkedList<E> &rhs) {
    length   = rhs.length;
    curr_pos = nullptr;

    if (this == &rhs)                   // leave on self-assignment
            return *this;
    
    if (rhs.front == nullptr) {         // Empty lists are copied easily
        front = nullptr;
        back = nullptr;
    } else {                            // Non-empty lists:  copy first node
        front = new Node;
        front->info = rhs.front->info;
        back->info = rhs.back->info;
        back->next = nullptr;
        Node *curr = front;
        Node *orig = rhs.front;

        while (orig->next != nullptr) { // then copy any/all subsequent nodes 
            curr->next = new Node;
            curr->next->info = orig->next->info;
            orig = orig->next;
            curr = curr->next;
        }

    }

    return *this;
}

template<typename E>
bool LinkedList<E>::isEmpty() {
    if(length==0) {
        return true;
    } else {
        return false;
    }
}

template<typename E>
void LinkedList<E>::clear() {
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
    back = nullptr;
}

template<typename E>
int LinkedList<E>::size() {
    return length;
}

template<typename E>
E LinkedList<E>::first() {
    if(isEmpty()) {
        throw runtime_error("cannot get first of empty list");
    }
    return front->info;
}

template<typename E>
E LinkedList<E>::last() {
    if(isEmpty()) {
        throw runtime_error("cannot get last of empty list");
    }
    return back->info;
}

template<typename E>
E LinkedList<E>::elementAt(int index) {
    if(index > length-1) {
        ostringstream oerr;
        oerr << "index (" << index << ") not in range [0.." << length << ")";
        string err = oerr.str();
        throw range_error(err);
    }
    curr_pos = front;
    for(int i = 0; i < index; i++) {
        curr_pos = curr_pos->next;
    }
    return curr_pos->info;
}

template<typename E>
void LinkedList<E>::print() {
    Node *node = new Node;
    node = nullptr;

    node = front;
    cout << "[LinkedList of size ";
    cout << size();
    cout << " <<";
    while (node != nullptr) {
        cout << (node->info);
        node = node->next;
    }
    cout << ">" << ">]" << endl;
}

template<typename E>
void LinkedList<E>::pushAtBack(E elem) {
    Node *node = new Node;
    node->info=elem;
    if(front == nullptr)
    {
        front = node;
        node->prev = nullptr;
        node->next = nullptr;
        back = node;
    }
    else
    {
        node->prev = back;
        back->next = node;
        node->next = nullptr;
        back = node;
    }
    length++;
}

template<typename E>
void LinkedList<E>::pushAtFront(E elem) {
    Node *node = new Node;
    if(front== nullptr)
    {
        front = node;
        node->prev = nullptr;
        node->info = elem;
        node->next = nullptr;
        back = node;
    }
    else
    {
        node->next = front;
        node->info = elem;
        node->prev = nullptr;
        front->prev = node;
        front = node;
    }
    length++;
}

template<typename E>
void LinkedList<E>::insertAt(E elem, int index) {
    if(index > length) {
        ostringstream oerr;
        oerr << "index " << index << " not in range [0.." << length << "]";
        string err = oerr.str();
        throw range_error(err);
    }
    curr_pos = front;
    if(index == 0) {
        pushAtFront(elem);
    } else if (index == size()) {
        pushAtBack(elem);
    } else {
        for(int i = 0; i < index; i++) {
            curr_pos = curr_pos->next;
        }
        Node *node = new Node;
        node->info = elem;
        curr_pos->prev->next = node;
        node->prev = curr_pos->prev;
        node->next = curr_pos;
        length++;
    }
}

template<typename E>
void LinkedList<E>::insertInOrder(E elem) {
    Node *temp;
    temp = front;
    int index = 0;
    while(temp->info < elem && temp->next != nullptr) {
        temp=temp->next; 
        index++;
    }
    if(index >= size() - 1) {
        pushAtBack(elem);
    } else {
        insertAt(elem, index);
    }
}

template<typename E>
void LinkedList<E>::popFromFront() {
    if(isEmpty()) {
        throw runtime_error("cannot pop from empty list");
    }
    if(front == back)
    {
        Node *cur;
        cur = front;
        front = nullptr;
        back = nullptr;
        delete cur;
    }
    else
    {
        Node *cur;
        cur = front;
        front = front->next;
        front->prev = nullptr;
        delete cur;
    }
    length--;
}

template<typename E>
void LinkedList<E>::popFromBack() {
    if(isEmpty()) {
        throw runtime_error("cannot pop from empty list");
    }
    if(front == back)
    {
        Node *cur;
        cur = front;
        front = nullptr;
        back = nullptr;
        delete cur;
    }
    else
    {
        Node *cur;
        cur = back;
        back = back->prev;
        back->next = nullptr;
        delete cur;
    }
    length--;
}

template<typename E>
void LinkedList<E>::removeAt(int index) {
    if(index > length) {
        ostringstream oerr;
        oerr << "index " << index << " not in range [0.." << length << ")";
        string err = oerr.str();
        throw range_error(err);
    }
    curr_pos = front;
    for(int i = 0; i < index-1; i++) {
        curr_pos = curr_pos->next;
    }
    curr_pos->next = curr_pos->next->next;
}

template<typename E>
void LinkedList<E>::replaceAt(E elem, int index) {
    if(index > length) {
        ostringstream oerr;
        oerr << "index " << index << " not in range [0.." << length << ")";
        string err = oerr.str();
        throw range_error(err);
    }
    curr_pos = front;
    for(int i = 0; i < index; i++) {
        curr_pos = curr_pos->next;
    }
    curr_pos->info = elem;
}

template<typename E>
void LinkedList<E>::concatenate(LinkedList &second) {
    if(isEmpty()) {
        front = second.front;
        curr_pos = second.curr_pos;
        back = second.back;
    }
    if(second.isEmpty()) {
        return;
    }
    back->next = second.front;
    length = size() + second.size();
}

template<typename E>
void LinkedList<E>::shrink() {
    back->next = nullptr;
}

template<typename E>
bool LinkedList<E>::find(E elem) {
    Node *temp;
    temp = front;
    while(temp != nullptr)
    {
        if(temp->info == elem)
        {
            return true;
            break;
        }
        temp=temp->next;
    }
    return false;
}

template class LinkedList<char>;
template class LinkedList<int>;


#endif

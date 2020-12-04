/*
 *  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  LinkedList.cpp
 *
 *  PURPOSE
 *
 *  Modified By:
 *           On:
 */

//
// NOTE:  Do a "monomorphic" implementation for char LinkedLists
// first, then turn all the functions into template functions.
//
// DO NOT FORGET TO UNCOMMENT THE LAST TWO LINES IN THIS FILE WHEN YOU
// MAKE YOUR TEMPLATES!
//

#include <iostream>
#include <sstream>
#include "LinkedList.h"

using namespace std;

// Default constructor
// template<class E>
// LinkedList<T>::LinkedList()

LinkedList::LinkedList()
{
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
    back = nullptr;
}



LinkedList::LinkedList(E elem) {
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

LinkedList::LinkedList(E elems[], int len) {
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
    back = nullptr;
    for(int i = 0; i < len; i++) {
        pushAtBack(elems[i]);
    }
}

LinkedList::LinkedList(const LinkedList &other) {
    length   = other.length;
    front    = other.front;
    curr_pos = front;
    back = other.back;
}

LinkedList::~LinkedList() {
    curr_pos = front;
    while(curr_pos) {
        Node* next = curr_pos->next;
        delete curr_pos;
        curr_pos = next;
    }
}

LinkedList &LinkedList::operator=(const LinkedList &rhs) {
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

bool LinkedList::isEmpty() {
    if(length==0) {
        return true;
    } else {
        return false;
    }
}

void LinkedList::clear() {
    length   = 0;
    front    = nullptr;
    curr_pos = nullptr;
    back = nullptr;
}

int LinkedList::size() {
    return length;
}

E LinkedList::first() {
    if(isEmpty()) {
        throw runtime_error("cannot get first of empty list");
    }
    return front->info;
}

E LinkedList::last() {
    if(isEmpty()) {
        throw runtime_error("cannot get last of empty list");
    }
    return back->info;
}

E LinkedList::elementAt(int index) {
    if(index > length-1) {
        ostringstream oerr;
        oerr << "index (" << index << ") not in range [0.." << length << ")";
        string err = oerr.str();
        throw range_error(err);
    }
}

void LinkedList::print() {
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

void LinkedList::pushAtBack(E elem) {
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

void LinkedList::pushAtFront(E elem) {
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
void LinkedList::insertAt(E elem, int index) {
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


void LinkedList::insertInOrder(E elem) {
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

void LinkedList::popFromFront() {
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

void LinkedList::popFromBack() {
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

void LinkedList::removeAt(int index) {
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

void LinkedList::replaceAt(E elem, int index) {
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

void LinkedList::concatenate(LinkedList &second) {
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

void LinkedList::shrink() {
    back->next = nullptr;
}

bool LinkedList::find(E elem) {
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

// template class LinkedList<char>;
// template class LinkedList<int>;

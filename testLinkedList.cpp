/*
 *  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  testLinkedList.cpp
 *
 *  PURPOSE
 *
 *  Modified By: Sam Lacet-Brown
 *           On: Sept 23rd, 2020
 */

#include <iostream>
#include "LinkedList.h"
using namespace std;

void test1() {
    LinkedList<char> test;
    cout << "Test 1: " << endl;
    test.print(); //
    test.pushAtBack('a');
    test.pushAtFront('n');
    test.pushAtBack('j');
    test.print(); //naj
    cout << "First: " << test.first() << endl; //n
    test.popFromBack();
    test.print(); //na
    test.pushAtBack('k');
    test.popFromFront();
    cout << "Last: " << test.last() << endl; //k
    test.print(); //ak
    test.clear();
    test.print(); //
}

void testthree() {
    char testing[] = "seventh";
    cout << endl;
    cout << "Test 3: " << endl;
    LinkedList<char> test3(testing, 7);
    test3.print();
    test3.insertInOrder('c');
    test3.print(); //cseventh
    test3.insertInOrder('n');
    test3.print(); //cnseventh
    test3.insertAt('h', 3);
    test3.insertInOrder('z');
    test3.print(); //cnhseventhz
    cout << "n?: " << test3.find('n') << endl; //1 (true)
    cout << "x?: " << test3.find('x') << endl; //0 (false)
}

int main()
{
    test1();
    cout <<endl;
    cout << "Test 2(a):" << endl;
    LinkedList<char> test2a;
    test2a.pushAtBack('a');
    test2a.pushAtFront('n');
    test2a.pushAtBack('j');
    test2a.print(); //
    cout << "Test 2: " << endl;
    LinkedList<char> test2('a');
    test2.print(); //a
    test2.concatenate(test2a);
    test2.print(); //anaj
    test2.replaceAt('x', 1);
    test2.print(); //axaj
    test2.removeAt(2);
    test2.print(); //axj
    LinkedList<char> test2c(test2);
    test2c.print(); //axj
    testthree();
}
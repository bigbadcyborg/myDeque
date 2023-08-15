/*
 * Author: Russell Sullivan
 * Assignment: project 9 Extra Credit
 * Date modified: 5/2/2019
 * Date due: 5/3/2019
 * File: proj9-driver.cpp
 */

#include <iostream>
#include "proj9-MyDeque.h"

using namespace std;

int main() {
    MyDeque<char> deque;

    //test pushFront
    cout << "Testing pushFront ...\n\nsending char values a-z ..." << endl;
    for( char i = 'a'; i <= 'z'; i++ )
        deque = deque.pushFront(i);
    cout << deque.toString();


    //test copy constructor
    cout << "\nTesting copy constructor ...\n" << endl;
    MyDeque<char> deque2 = deque;
    cout << deque2.toString();


    //testing overloaded assignment operator
    cout << "\nTesting overloaded assignment operator ...\n" << endl;
    MyDeque<char> deque5;
    deque5.pushBack('x');
    deque5 = deque;
    cout << deque5.toString();


    //test pushBack
    cout << "\nTesting pushBack ...\n\nsending char values a-z ..." << endl;
    MyDeque<char> deque3;       //new empty deque
    for( char i = 'a'; i <= 'z'; i++ )
        deque3 = deque3.pushBack(i);
    cout << deque3.toString();
    cout << "Testing when rear meets front ..." << endl;
    MyDeque<char> deque4;       //new empty deque
    for( char i = 'a'; i <= 'e'; i++ )
        deque4 = deque4.pushFront(i);
    for( char i = 'f'; i <= 'k'; i++ )
        deque4 = deque4.pushBack(i);
    cout << deque4.toString();


    //test operator[]
    cout << "\nTesting overloaded operator[] ...\n" << endl;
    cout << "deque4's 6th element: " << deque4[5] << endl;
    cout << "deque4's data:\n";
    for( int i = 0; i < deque4.getSize(); i++ )
        cout << deque4[i] << " ";


    //test popFront
    cout << "\n\nTesting popFront ...\n" << endl;
    char removed;
    deque4 = deque4.popFront( removed );
    cout << "Removed: " << removed << endl << deque4.toString();
    cout << "Removing values: ";
    const int deque4Size = deque4.getSize();
    for( int i = 0; i < deque4Size; i++ ) {
        deque4 = deque4.popFront(removed);
        cout << removed << " ";
    }
    cout << endl << deque4.toString();


    //test popBack
    cout << "\n\nTesting popBack ...\n" << endl;
    deque = deque.popBack( removed );        //popping the first deque created ( z - a )
    cout << "Removed: " << removed << endl << deque.toString();


    //Testing mixture of pushBack and pushFront
    cout << "\nTesting mixture of pushBack and pushFront ...\n" << endl;
    MyDeque<char> dequeMix; //cool name huh
    for( char i = 'a'; i <= 'f'; i++ )
        dequeMix = dequeMix.pushFront(i);
    for( char i = 'z'; i >= 'w'; i-- )
        dequeMix = dequeMix.pushBack(i);
    cout << dequeMix.toString();
    dequeMix.pushBack('x');
    cout << dequeMix.toString();

    dequeMix.erase();
    for( char i = 'a'; i <= 'f'; i++ )
        dequeMix = dequeMix.pushFront(i);
    for( char i = 'z'; i >= 'w'; i-- )
        dequeMix = dequeMix.pushBack(i);
    cout << dequeMix.toString();
    dequeMix.pushFront('x');
    cout << dequeMix.toString();


    //test errors
    cout << "\nTesting exception errors ...\n" << endl;

    MyDeque<char> emptyDeque;
    //attempt to popFront empty deque
    try{
        cout << "Attempting to popFront empty deque ...\n";
        emptyDeque.popFront( removed );
    } catch( BADINDEX ) {
        cout << "Error: cannot popFront on empty deque.\n\n";
    }

    //attempt to popBack empty deque
    try{
        cout << "Attempting to popBack empty deque ...\n";
        emptyDeque.popBack( removed );
    } catch( BADINDEX ) {
        cout << "Error: cannot popBack empty deque.\n\n";
    }


    //attempt front() on empty deque
    try{
        cout << "Attempting to call front() on empty deque...\n";
        char front = emptyDeque.front();
    } catch( BADINDEX ) {
        cout << "Error: cannot call front() on empty deque.\n\n";
    }

    //attempt back() on empty deque
    try{
        cout << "Attempting to call back() on empty deque ...\n";
        char back = emptyDeque.back();
    } catch( BADINDEX ) {
        cout << "Error: cannot call back() on empty deque.\n\n";
    }

    //attempt to segfault with overloaded operator[]
    cout << "Attempting to seg fault with overloaded operator[] ...\n";
    try{
        cout << "dequeMix data: ";
        for( int i = 0; i < 99; i++ )
            cout << dequeMix[i] << " ";
    } catch ( BADINDEX ) {
        cout << "\nError: segmentation fault by operator[].\n\n";
    }

    //attempt to segfault with negative index
    cout << "Attempting to segfault with negative index ...\n";
    try{
        cout << dequeMix[-1];
    } catch ( BADINDEX ) {
        cout << "Error: segmentation fault by operator[] with negative index.\n\n";
    }


    return 0;
}
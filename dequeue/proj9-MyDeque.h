/*
 * Author: Russell Sullivan
 * Assignment: project 9 Extra Credit
 * Date modified: 5/2/2019
 * Date due: 5/3/2019
 * File: proj9-MyDeque.h
 */

#ifndef DEQUEUE_PROJ9_MYDEQUE_H
#define DEQUEUE_PROJ9_MYDEQUE_H

#include <sstream>
#include <iostream>
#include "proj9-ContainerIfc.h"

using namespace std;

template <class T>
class MyDeque : public ContainerIfc<T> {
public:
    MyDeque ();
    ~ MyDeque ();
    MyDeque (const MyDeque&);
    MyDeque <T>& operator = (const MyDeque&);
    MyDeque <T>& pushFront(T);
    MyDeque <T>& pushBack(T);
    MyDeque <T>& popFront(T&); // throws BADINDEX
    MyDeque <T>& popBack(T&); // throws BADINDEX
    T front(); // throws BADINDEX
    T back(); // throws BADINDEX
    T& operator [](int); // throws BADINDEX
    int getSize();
    bool isEmpty();
    void erase();
    string toString();

protected:
    T *data;
    int size, capacity, begin, rear;
    bool allocatedData;             //true if data has been dynamically allocated, false otherwise
                                    //(for when erase() has been used and a push is attempted on an object)

    void pushBackSplitGrow();
    void pushFrontSplitGrow();
    void grow();
};

/*========================================================================================================
 * function: MyDeque ()
description: class constructor
pre-condition: none
post-condition: class object created with size = 0 ,capacity = 10, begin = -1, rear = -1,
data points to an array of size capacity and type T
return: nothing
 ========================================================================================================*/
template<class T>
MyDeque<T>::MyDeque() {
    this->size = 0;
    this->capacity = 10;
    this->begin = -1;
    this->rear = -1;
    this->data = new T[this->capacity];
    this->allocatedData = true;
}


/*=========================================================================================================
 * function: toString()
 * sends object's private data to string stream
 * returns the stream in string form
 ========================================================================================================*/
template< class T >
string MyDeque<T>::toString(){
    ostringstream out;
    out << "Size: " << this->size << endl;
    out << "Capacity: " << this->capacity << endl;
    out << "Data:\n";

    if( this->size != 0) {
        for (int i = begin, k = 0; k < (this->size - 1); i = (i + 1) % this->capacity, k++) {
            out << data[i] << " ";
        }
        out << data[rear];
        out << endl;
    }

    return out.str();
}


/*=========================================================================================================
 * function: ~ MyDeque ()
description: class destructor
pre-condition: a MyDeque object exists
post-condition: all memory allocated to the MyDeque is deleted
return: nothing
 ========================================================================================================*/
template<class T>
MyDeque<T>::~MyDeque() {
    delete [] this->data;
    this->allocatedData = false;
}


/*=========================================================================================================
 * function: splitGrowForPushFront()
 * saves current dynamic array and copies data over to new dynamic array of twice the capacity
 * adds n-1 spaces between front and rear, where n is this->capacity
 ========================================================================================================*/
template<class T>
void MyDeque<T>::pushFrontSplitGrow() {
    //save data
    T* temp = data;
    int oldFront = this->begin;
    int oldCap = this->capacity;


    //adjust new attributes
    this->begin = oldCap + this->begin;
    this->capacity *= 2;


    //copy data over (circularly)
    this->data = new T[this->capacity];
    for( int i = oldFront, k = begin, g = 0; g < this->size;
            i = ( i + 1 ) % oldCap, k = ( k + 1 ) % this->capacity, g++ ) {
        this->data[k] = temp[i];
    }


    delete temp;
}


/*=========================================================================================================
 * function: pushFront(T e)
description: add data element e to the front of the vector
pre-condition: a MyDeque object exists
post-condition: if size == capacity, double capacity, add to the front of the array using
begin data element e has been added to the front of the array, increment
size
return: a reference to self
 ========================================================================================================*/
template<class T>
MyDeque<T> &MyDeque<T>::pushFront( T val ) {
    //grow if full
    if (this->size == this->capacity)
        pushFrontSplitGrow();

    //construct if empty and has no dynamically allocated memory (erase() was used on object)
    if( this->size == 0 && !this->allocatedData) {
        this->size = 0;
        this->capacity = 10;
        this->begin = -1;
        this->rear = -1;
        this->data = new T[this->capacity];
        this->allocatedData = true;
    }

    //circular wrap scenario
    if (this->begin == 0) {
        this->begin = this->capacity - 1;       //beginning is now at last element
        this->data[begin] = val;
        this->size++;
    }//empty scenario w/ already dynamically allocated data
    else if (this->size == 0 && this->allocatedData) {
        this->begin = 0;
        this->rear = 0;
        this->data[begin] = val;
        this->size++;
    //normal scenario
    } else {
        this->begin--;
        this->data[this->begin] = val;
        this->size++;
    }

    return *this;
}


/*=========================================================================================================
 * function: MyDeque (const MyDeque & v)
description: class copy constructor
pre-condition: a MyDeque object exists
post-condition: a copy of the class object v is made
return: nothing
 ========================================================================================================*/
template<class T>
MyDeque<T>::MyDeque(const MyDeque &that) {
    if( this != &that ){
        this->size = that.size;
        this->capacity = that.capacity;
        this->begin = that.begin;
        this->rear = that.rear;

        this->data = new T[this->capacity];
        for( int i = 0; i < this->capacity; i++ )
            this->data[i] = that.data[i];
    }
}


/*=========================================================================================================
 * function: operator =(const MyDeque & v)
description: overloaded assignment operator
pre-condition: a object exists
post-condition: the object n is unchanged and *this is an exact copy of n
return: a reference to self
 ========================================================================================================*/
template<class T>
MyDeque<T> &MyDeque<T>::operator=(const MyDeque &that) {

    if( this != &that ){
        this->erase();

        this->size = that.size;
        this->capacity = that.capacity;
        this->begin = that.begin;
        this->rear = that.rear;

        this->data = new T[this->capacity];
        for( int i = 0; i < this->capacity; i++ )
            this->data[i] = that.data[i];
    }

    return *this;

}


/*=========================================================================================================
 * function: erase()
description: erases a vector
pre-condition: a object exists
post-condition: the elements of a MyDeque are erased and all data members are set to
default values
return: nothing
 ========================================================================================================*/
template<class T>
void MyDeque<T>::erase() {

        this->begin = -1;
        this->rear = -1;
        this->size = 0;
        this->capacity = 10;

        delete[] this->data;
        this->allocatedData = false;

}


//splitGrowForPushBack
template<class T>
void MyDeque<T>::pushBackSplitGrow(){
    //save old stuff
    T* temp = this->data;
    int oldBegin = this->begin;
    int oldCap = this->capacity;

    //update new stuff
    this->capacity *= 2;
    this->begin = this->begin + oldCap;
    this->data = new T[this->capacity];

    //copy data over
    for( int i = 0, k = this->begin, j = oldBegin; i < this->size;
            k = ( k + 1 ) % this->capacity, j = ( j + 1 ) % oldCap, i++ ){
        this->data[k] = temp[j];
    }

    delete temp;

}


/*=========================================================================================================
 * function: pushBack(T e)
description: store data element e in end of the vector
pre-condition: a MyDeque object exists
post-condition if size == capacity, double capacity, data element e has been
added to the end of the array using rear, increment size
return: a reference to self
 ========================================================================================================*/
template<class T>
MyDeque<T> &MyDeque<T>::pushBack(T val) {
    //if full, double capacity
    if( this->size == this->capacity && this->rear == ( this->size - 1 ) )
        grow();


    //construct if empty and has no dynamically allocated memory (erase() was used on object)
    if( this->size == 0 && !this->allocatedData ){
        this->size = 0;
        this->capacity = 10;
        this->begin = -1;
        this->rear = -1;
        this->data = new T[this->capacity];
        this->allocatedData = true;
    }


    //if empty
    if( this->size == 0 && this->allocatedData ){
        this->begin = 0;
        this->rear = 0;
        this->data[rear] = val;
        this->size++;
    }
    else{
      if( ( ( rear + 1 ) % this->capacity ) == this->begin )
          pushBackSplitGrow();
      this->rear = ( rear + 1 ) % this->capacity;
      this->data[rear] = val;
      this->size++;
    }

    return *this;
}


/*=========================================================================================================
 * function: grow()
 * saved current data array and creates a new dynamically allocated array of twice the capacity then copies
 * the original data over to the new one
 ========================================================================================================*/
template<class T>
void MyDeque<T>::grow() {
    //save data
    T* temp = this->data;

    this->capacity *= 2;

    //make new array
    this->data = new T[this->capacity];

    //copy temp over
    for( int i = 0; i < this->size; i++ )
        this->data[i] = temp[i];

    delete temp;
}


/*=========================================================================================================
 * function: popFront(T& e)
description: removes a data element from the front of the data structure (MyDeque)
pre-condition: a object exists
post-condition: the first element has been removed from the front of the MyDeque,
 decrement size, and set e equal to the element removed, error if
 MyDeque is empty
return: a reference to self

 ========================================================================================================*/
template<class T>
MyDeque<T> &MyDeque<T>::popFront(T &val) {
    //empty case
    if( this->size == 0 )
        throw BADINDEX();


    val = this->data[begin];

    if( this->begin == this->rear ){    //if removing the last number in the list
        this->begin = -1;
        this->rear = -1;
    }
    else
        this->begin = ( this->begin + 1 ) % this->capacity;

    this->size--;


    return *this;
}


/*=========================================================================================================
 * function: popBack(T& e)
description: removes a data element from the rear (end) of the data
structure (MyDeque)
pre-condition: a object exists
post-condition: a data element has been removed from the rear of the MyDeque,
 decrement currentSize, and set e equal to the element removed, error if
MyDeque is empty
return: a reference to self
 ========================================================================================================*/
template<class T>
MyDeque<T> &MyDeque<T>::popBack(T &val) {
    //empty case
    if( this->size == 0 )
        throw BADINDEX();


    val = this->data[rear];

    if( this->begin == this->rear ){    //if removing the last number in the list
        this->begin = -1;
        this->rear = -1;
    }
    else{
        if( this->rear == 0 )   //wrap scenario
            this->rear = this->capacity - 1;
        else
            this->rear--;
    }


    this->size--;


    return *this;

}


/*=========================================================================================================
 * function: front()
description: returns a copy of the first data item in the MyDeque
pre-condition: a object exists
post-condition: the object is unchanged, error if MyDeque is empty
return: a copy of the object at the beginning of the array
 ========================================================================================================*/
template<class T>
T MyDeque<T>::front() {
    if( this->size == 0 )
        throw BADINDEX();

    return this->data[this->begin];
}


/*=========================================================================================================
 * function: back()
description: returns a copy of the last data item in MyDeque
pre-condition: a object exists
post-condition: the object is unchanged, error if MyDeque is empty
return: a copy of the object at the end of the array
 ========================================================================================================*/
template<class T>
T MyDeque<T>::back() {
    if( this->size == 0 )
        throw BADINDEX();

    return this->data[this->rear];
}


/*=========================================================================================================
 * function: operator [](int n)
description: returns a reference to data element n in MyDeque
pre-condition: a object exists
post-condition: the object is unchanged, error: n >= size or n < 0
return: a reference to the object stored at offset of n from the front of the array
 within data
 ========================================================================================================*/
template<class T>
T &MyDeque<T>::operator[](int n) {
    if( n >= this->size || n < 0 )
        throw BADINDEX();


    int ndx = this->begin;
    //go to nth element from beginning of array
    for( int i = 0; i < n; i++ ){
        ndx = ( ndx + 1 ) % this->capacity;
    }

    return this->data[ndx];
}


/*=========================================================================================================
 * function: getSize()
description: returns the number of elements currently in the MyDeque
pre-condition: a object exists
post-condition: the MyDeque is unchanged
return: an integer value representing the number of elements in the list
 ========================================================================================================*/
template<class T>
int MyDeque<T>::getSize() {
    return this->size;
}


/*=========================================================================================================
 * function: isEmpty()
description: returns state information about the list
pre-condition: a object exists
post-condition: the MyDeque is unchanged
return: true if the MyDeque is empty false otherwise
 ========================================================================================================*/
template<class T>
bool MyDeque<T>::isEmpty() {
    if( this->size == 0 )
        return true;
    else
        return false;
}


#endif //DEQUEUE_PROJ9_MYDEQUE_H

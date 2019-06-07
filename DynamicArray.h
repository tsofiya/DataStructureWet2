//
// Created by lucio on 6/2/2019.
//

#ifndef WET2_DYNAMICARRAY_H
#define WET2_DYNAMICARRAY_H

#include <iostream>
#include "DynamicArrayExceptions.h"

template<class T>

class DynamicArray {


private:
    int myCapacity;
    int mySize;
    T* myArray;

public:

    DynamicArray(const int capacity=1) : myCapacity(capacity), mySize(0), myArray(
            nullptr){

            if (capacity<1){
                throw IllegalArgument();
            }
            myArray = new T [capacity];
            if (!myArray){
                throw std::bad_alloc();
        }
        for (int i=0; i<capacity; i++){
            myArray[i]=NULL;
        }
    }

    ~DynamicArray() = default;


    void expand(){
        int temp=myCapacity*2;
        T* tempArray = new T [temp];
        for (int i=0; i<temp; i++){
            tempArray[i]=NULL;
        }
        for (int i=0; i<myCapacity; i++){
            tempArray[i]= T (myArray[i]);
        }
        delete[]myArray; //todo: is this right? memory leak??
        myArray=tempArray;
        myCapacity=temp;
    }

    void shrink (){
        int temp=myCapacity/2;
        T* tempArray = new T [temp];
        if (!tempArray){
            throw  std::bad_alloc();
        }
        for (int i=0; i<temp; i++){
            tempArray[i]=NULL;
        }
        for (int i=0; i<=mySize; i++){
            tempArray[i]= T(myArray[i]);
        }
        delete[]myArray; //todo: is this right? memory leak??
        myArray=tempArray;
        myCapacity=temp;
    }

    void push (const T& element) {
    /*    if (element==NULL) {
            throw IllegalArgument();
        }
        */
        myArray[mySize + 1] = element;
        mySize++;
            if (mySize == myCapacity-1) {
                this->expand();
            }
    }

    T& pop (){
        if (mySize==0){
            throw Failure();
        }
        mySize--;
        if (mySize <= (myCapacity / 4)) {
            shrink();
        }
        return myArray[mySize+1];
    }

    void printArray (){
        for (int i=0; i<myCapacity;i++){
            std::cout << "("<<myArray[i]<<"), "<<std::endl;
        }
    }

    int getSize(){
        return mySize;
    }

    int getCapacity(){
        return myCapacity;
    }

};

#endif //WET2_DYNAMICARRAY_H

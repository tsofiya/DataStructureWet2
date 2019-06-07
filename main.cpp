#include <iostream>

#include "DynamicArray.h"
#include "HashTable.h"
#include "DynamicArrayExceptions.h"

int main() {

HashTable<int> hash= HashTable<int>(10);
    hash.printHashTable();

    hash.insert(1,2);
    hash.printHashTable();
    hash.insert(2,2);
    hash.printHashTable();
    hash.insert(11,3);
    hash.printHashTable();
    hash.insert(21,7);
    hash.printHashTable();
    hash.insert(0,5);
    hash.insert(31,7);
    hash.insert(10,39);
    hash.insert(7,5);
    hash.insert(24,9);
    hash.printHashTable();
    hash.expand();
    hash.printHashTable();












}
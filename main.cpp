#include <iostream>
#include "Schedule2.h"

#include "DynamicArray.h"
#include "HashTable.h"
#include "Wet2Exceptions.h"

int main() {

    std::cout << "Hello, World!" << std::endl;
    //Schedule2 s(8);
    HashTable<int> hash = HashTable<int>(10);
    hash.printHashTable();
    hash.insert(1, 2);
    hash.printHashTable();
    hash.insert(2, 2);
    hash.printHashTable();
    hash.insert(11, 3);
    hash.printHashTable();
    hash.insert(21, 7);
    hash.printHashTable();
    hash.insert(0, 5);
    hash.insert(31, 7);
    hash.insert(10, 39);
    hash.insert(7, 5);
    hash.insert(24, 9);
    hash.printHashTable();
    hash.expand();
    hash.printHashTable();
}
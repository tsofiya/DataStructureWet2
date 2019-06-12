#include <iostream>

#include "DynamicArray.h"
#include "HashTable.h"
#include "BiDirectionalList.h"
#include "DynamicArrayExceptions.h"

int main() {

HashTable<int> hash= HashTable<int>(10);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.insert(1,2);
    hash.printHashTable();
    std::cout<<std::endl;

    hash.insert(2,2);
    hash.printHashTable();
    std::cout<<std::endl;

    hash.insert(11,3);
    hash.printHashTable();
    std::cout<<std::endl;

    hash.insert(21,7);
    hash.printHashTable();
    std::cout<<std::endl;

    hash.insert(0,5);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.insert(31,7);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.insert(10,39);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.insert(7,5);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.insert(24,9);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.printHashTable();

    hash.expand();
    hash.printHashTable();
    hash.shrink();
    hash.printHashTable();
    std::cout<<std::endl;
    std::cout << hash.member(24)<< std::endl;
    std::cout << hash.member(25)<< std::endl;
    std::cout << hash.member(7)<< std::endl;
    std::cout << hash.member(10)<< std::endl;
    std::cout << hash.member(2)<< std::endl;
    std::cout << hash.member(1)<< std::endl;
    std::cout << hash.member(31)<< std::endl;
    std::cout << hash.member(0)<< std::endl;
    std::cout << hash.member(247)<< std::endl;
    std::cout << hash.member(2984)<< std::endl;
    std::cout << hash.member(0)<< std::endl;
    std::cout << hash.member(0)<< std::endl;
    std::cout << hash.member(24)<< std::endl;



    std::cout << "24: " << hash.getDataByKey(24)<< std::endl;
    std::cout << "2: " << hash.getDataByKey(2)<< std::endl;
    std::cout << "0: " << hash.getDataByKey(0)<< std::endl;
    std::cout << "24: " << hash.getDataByKey(24)<< std::endl;
    std::cout << "31: " << hash.getDataByKey(31)<< std::endl;
    std::cout << "1: " << hash.getDataByKey(1)<< std::endl;
    std::cout << "10: " << hash.getDataByKey(10)<< std::endl;


    hash.deleteElement(21);
    std::cout << " Deleted 21 successfully. " << std::endl;

    hash.printHashTable();
    std::cout<<std::endl;


    hash.deleteElement(7);
    std::cout << " Deleted 7 successfully. " << std::endl;

    hash.printHashTable();
    std::cout<<std::endl;
    std::cout << " Ok looks like were done here. " << std::endl;


    /*

    hash.deleteElement(24);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(7);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(2);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(31);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(0);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(11);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(10);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(24);
    hash.printHashTable();
    std::cout<<std::endl;
    hash.deleteElement(1);
    hash.printHashTable();
    std::cout<<std::endl;
*/

return 0;
}
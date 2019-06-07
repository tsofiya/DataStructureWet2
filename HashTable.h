//
// Created by lucio on 6/6/2019.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "BiDirectionalList.h"
#include "DynamicArray.h"
#include "DynamicArrayExceptions.h"

template<class T>

class HashTable{


public:
    class KeyAndData{
    private:
        int key;
        T data;
    public:
        KeyAndData (const int k=1, const T& d=NULL): key(k), data(d){}

        int getKey(){
            return key;
        }
        T& getData(){
            return data;
        }
    };

private:

    int tableSize;
    int insertedCounter;
    BiDirectionalList<KeyAndData> * table;

public:

    HashTable (int ts=1) : tableSize(ts){
        insertedCounter=0;
        table = new BiDirectionalList<KeyAndData>[tableSize];
        for (int i=0; i<tableSize; i++){
            table[i]=NULL;
        }
    }

    ~HashTable(){
        delete[](table);
    }
    //todo: ASK: should we change this to "k%tableSize" ??
    // should we make the default size 22 or something, and then it will forever remain the same? or nah?
    //how does the growth factor here matter when resizing?
    int hashFunction(const int k){
        return (k%tableSize);
        //return (k%size??);
    }

    int getTableSize(){
        return tableSize;
    }
    int getInsertedCounter(){
        return insertedCounter;
    }

//todo: important: this function may cause the array to be ready to expand;
//shedule2 will have ownership over this process, since it knows what M is defined to be!
    void insert (const int key, const T& data){

        KeyAndData current = KeyAndData(key, data);
        int position = hashFunction(key);
        table[position].push(current);  //todo: test for Memory leak (maybe regular test will do)
        insertedCounter++;
    }

    void deleteElement (const int key){

        int position=hashFunction(key);
        if (!table[position].getHead()){
            throw ElementDoesNotExist();
        }
        Node<KeyAndData>* n= table[position].getHead();
        while (n){
        KeyAndData current = n->data;
            if (current.getKey()==key){
                table[position].removeNode(n);
                insertedCounter--;
                return;
            }
            Node<KeyAndData>* temp = n;
            n=temp->next;
        }
        if (!n){
            throw ElementDoesNotExist();
        }
    }

    bool member (const int key){

        int position=hashFunction(key);
        if (!table[position].getHead()){
            return false;
        }
        Node<KeyAndData>* n= table[position].getHead();
        while (n){
            KeyAndData current = n->data;
            if (current.getKey()==key){
                return true;
            }
            Node<KeyAndData>* temp = n;
            n=temp->next;
        }
        if (!n){
            return false;
        }
    }


void expand (){

    int temp=tableSize*2;
    BiDirectionalList<KeyAndData>* newTable = new BiDirectionalList<KeyAndData>[temp]; //may throw bad_alloc();
    for (int i=0; i<temp; i++){
        newTable[i]=NULL;
    }
    for (int i=0; i<tableSize; i++){
        newTable[i]= BiDirectionalList<KeyAndData>(table[i]);
    }
    delete[]table; //todo: is this right? memory leak??
    table=newTable;
    tableSize=temp;
}

    void shrink(){

        int temp=tableSize/2;
        BiDirectionalList<KeyAndData>* newTable = new BiDirectionalList<KeyAndData>[temp]; //may throw bad_alloc();
        for (int i=0; i<temp; i++){
            newTable[i]=NULL;
        }
        for (int i=0; i<tableSize; i++){
            newTable[i]= BiDirectionalList<KeyAndData>(table[i]);
        }
        delete[]table; //todo: is this right? memory leak??
        table=newTable;
        tableSize=temp;
    }

    /*void printHashTable() {

        BiDirectionalList<KeyAndData> current_lst;
        Node<KeyAndData> *current_node;
        Node<KeyAndData> *temp;

        KeyAndData current_kad;
        int current_key;
        T current_data;
        printf("Key\t||\tData\n");


        for (int i = 0; i < tableSize; i++) {
            if (table[i].getHead()==NULL){
                std::cout << "(Hash Cell " << i << "):";
                std::cout << " =====> |_NULL_|";
                printf("=>End--\n");
                continue;
            }
            current_lst = table[i];
            current_node = table[i].getHead();

            current_kad = table[i].getHead()->data;
            current_key = current_kad.getKey();
            current_data = current_kad.getData();
            std::cout << "(Hash Cell " << i << "):";
            while (current_node) {
                current_kad = table[i].getHead()->data;
                current_key = current_kad.getKey();
                current_data = current_kad.getData();
                std::cout << " =====> |_ Key:" << current_key << " Data:"
                          << current_data << "_| ";
                temp = current_node;
                current_node = temp->next;
            }

            printf("=>End--\n");
        }
    }
     */

    friend ostream &operator<<(ostream &os, KeyAndData &kd) {
        os << "|_Key: " << kd.getKey();
        os << " Data:" << kd.getData() <<"_|";
        return os;
    }

    void printHashTable() {
        for (int i = 0; i < tableSize; i++) {
            std::cout <<"Table Cell: "<< i;
            std::cout <<"->";
            std::cout << table[i];
            std::cout << std::endl;
        }
    }

};



#endif //WET2_HASHTABLE_H

//
// Created by tsofi on 23/04/2019.
//

#ifndef WET1DATASTRUCTURES_AVLTREE_H
#define WET1DATASTRUCTURES_AVLTREE_H

#include "Wet2Exceptions.h"

using namespace Wet2Utils;

#include <iostream>


template<class K, class T>
class AVLtree {
private:
    typedef struct Node_t {
        Node_t *rightSon;
        Node_t *leftSon;
        int height;
        K key;
        T data;
    } Node;

    Node *root;
    int size;

public:
    AVLtree() : size(0) {
        root = NULL;
    }

    AVLtree(const AVLtree& other){
        recCopy(other.root);
    }


    ~AVLtree() {
        deleteTree(root);
    }

    void insert(const K &key, const T &data) {
        if (!root) {
            root = new Node{NULL, NULL, 0, K(key), T(data)};
            size++;
            return;
        }

        Node *n = new Node{NULL, NULL, 0, K(key), T(data)};
        recInsert(n, root);
        size++;

    }

    T& getDataByKey(const K& k){
        return recGetDataByKey(root, k);
    }

    void remove(const K &key) {
        recRemoval(root, NULL, key);
        size--;
    }

    //may throw an exception.
    AVLtree& mergeTrees(const AVLtree& other){
        AVLtree rTree(other);
        rTree.addTreeToTree(this);
        return rTree;
    }

    //Return the data for a certain key. If the key does not exist, throws KeyNotExist();
    Node* getByKey(const K &key) {
        return recGetByKey(root, key);
    }

    void addTreeToTree(AVLtree& tree){
        if (tree.root==NULL) return;
        addTreeToTreeRec(tree.root);
    }

    void preOrderPrint() {
        preOrder(root);
        std::cout << std::endl;
    }


    T* getAllData() {
        if (size == 0) {
            return NULL;
        }
        T* dataArray = new T[size];
        int *pos = new int;
        *pos = -1;
        recGetAllData(root, dataArray, pos);
        delete (pos);
        return dataArray;
    }

    int getTreeSize(){
        return size;
    }

    bool elementExistsByKey(const K& key){
        return recElementExistsByKey(root, key);
    }

    void ChangeKey(K& lastK, K& newK){
        T d= getByKey(lastK);
        remove(lastK);
        insert(newK, d);
    }


private:
    void recCopy(Node* n){
        if (n==NULL)
            return;
        insert(n->key, n->data);
        recCopy(n->rightSon);
        recCopy(n->leftSon);
    }

    void preOrder(Node *root) {
        if (root != NULL) {
            std::cout << "("<<root->key << ", "<<root->data<<") ";
            preOrder(root->leftSon);
            preOrder(root->rightSon);
        }

    }

    void addTreeToTreeRec(Node*n){
        Node* exist= getByKey(n->key);
        if (exist!=NULL) {
            insert(n->key, n->data);
        }
        else
            exist->data= exist->data+n->data;

        if (n->rightSon!=NULL)
            addTreeToTreeRec(n->rightSon);
        if (n->leftSon!=NULL)
            addTreeToTreeRec(n->leftSon);
    }

//this can throw an exception, but it shouldnt...
    bool recElementExistsByKey(Node*n, const K& key){
        if (n==NULL) {
            return false;
        }
        if (n->key==key) {
            return true;
        }
        else {
            if (key < n->key) {
                return recElementExistsByKey(n->leftSon, key);
            }
            else {
                return recElementExistsByKey(n->rightSon, key);
            }
        }
    }

    void recGetAllData(Node *curr, T *dataArray, int *pos){
        if (curr == NULL)
            return;
        (*pos)++;
        dataArray[*pos] = T(curr->data);
        recGetAllData(curr->leftSon, dataArray, pos);
        recGetAllData(curr->rightSon, dataArray, pos);
    }


    Node* recGetByKey(Node *n, const K &key) {
        if (n == NULL)
            NULL;
        if (n->key == key) {
            return n;
        } else {
            if (key < n->key) {
                return recGetByKey(n->leftSon, key);
            } else {
                return recGetByKey(n->rightSon, key);
            }
        }
    }

    void recRemoval(Node *n, Node *f, const K &key) {
        if (n == NULL)
            return;
        if (n->key < key)
            recRemoval(n->rightSon, n, key);
        else if (n->key > key)
            recRemoval(n->leftSon, n, key);
        else if (n->leftSon == NULL && n->rightSon == NULL) {
            if (f != NULL) {
                if (f->leftSon == n) {
                    f->leftSon = NULL;
                } else if (f->rightSon == n) {
                    f->rightSon = NULL;
                }
                delete (n);
                return;
            } else {

                delete (n);
                root = NULL;
                return;
            }
        } else if (n->leftSon == NULL) {
            Node *temp = n->rightSon;
            n->rightSon = temp->rightSon;
            n->leftSon = temp->leftSon;
            n->key = K(temp->key);
            n->data = T(temp->data);
            delete (temp);
        } else if (n->rightSon == NULL) {
            Node *temp = n->leftSon;
            n->rightSon = temp->rightSon;
            n->leftSon = temp->leftSon;
            n->key = temp->key;
            n->data = temp->data;
            delete (temp);
        } else {
            Node *temp= findMostLeft(n->rightSon, n);
            n->key = temp->key;
            n->data = temp->data;
            n->height = calcHeight(n);
            temp->key = key;
            //recRemoval(n, f, key);
        }

        n->height = calcHeight(n);
        preformRotation(n);
    }

    Node* findMostLeft(Node* curr, Node* f){
        if (curr->leftSon==NULL){
            f->leftSon= NULL;
            f->height= calcHeight(f);
            preformRotation(curr);
            return curr;
        }

        Node* rn= findMostLeft(curr->leftSon, curr);
        curr->height= calcHeight(curr);
        preformRotation(curr);
        return rn;
    }

    void deleteTree(Node *n) {
        if (n == NULL)
            return;
        deleteTree(n->leftSon);
        deleteTree(n->rightSon);
        delete (n);
    }

    //Todo: this is the problematic function causing a segmentation fault
    void recInsert(Node *in, Node *curr) {
        if (in->key < curr->key) {
            if (curr->leftSon == NULL) {
                curr->leftSon = in;
            } else
                recInsert(in, curr->leftSon);
        } else {
            if (curr->rightSon == NULL) {
                curr->rightSon = in;
            } else
                recInsert(in, curr->rightSon);
        }

        curr->height = calcHeight(curr);
        preformRotation(curr);
    }

    //Decides if a rotation is required and preforms a rotation if necessary.
    void preformRotation(Node *curr) {
        int balance = getNodeBalance(curr);
        if (balance == 2) {
            if (getNodeBalance(curr->leftSon) == -1)
                lrRotation(curr);
            else if (getNodeBalance(curr->leftSon) >= 0)
                llRotation(curr);
        }
        if (balance == -2) {
            if (getNodeBalance(curr->rightSon) == 1)
                rlRotation(curr);
            else if (getNodeBalance(curr->leftSon) <= 0)
                rrRotation(curr);
        }
    }


    // Get Balance factor of a specific node
    int getNodeBalance(Node *N) {
        if (N == NULL)
            return 0;
        if (N->rightSon == NULL && N->leftSon == NULL)
            return 0;
        if (N->rightSon == NULL)
            return N->leftSon->height + 1;
        if (N->leftSon == NULL)
            return -1 - N->rightSon->height;
        return (N->leftSon->height) - (N->rightSon->height);
    }

    int calcHeight(Node *n) {
        if (n->rightSon == NULL && n->leftSon == NULL)
            return 0;
        if (n->rightSon == NULL)
            return 1 + n->leftSon->height;
        if (n->leftSon == NULL)
            return 1 + n->rightSon->height;
        return 1 + max(n->leftSon->height, n->rightSon->height);
    }

    //preform LL rotation
    //TODO: not updated to be rank.
    void llRotation(Node *a) {
        Node *b = a->leftSon;
        Node *moveA = new Node{
                a->rightSon,
                b->rightSon,
                0,
                K(a->key),
                T(a->data)

        };
        moveA->height = calcHeight(moveA);
        a->data = T(b->data);
        a->key = K(b->key);
        a->leftSon = b->leftSon;
        a->rightSon = moveA;
        delete (b);
    }

    //preform LR rotation
    //TODO: not updated to be rank.
    void lrRotation(Node *a) {
        Node *b = a->leftSon;
        Node *c = b->rightSon;
        Node *moveA = new Node{
                a->rightSon,
                c->rightSon,
                0,
               K(a->key),
               T(a->data)
        };
        moveA->height = calcHeight(moveA);
        a->rightSon = moveA;
        a->leftSon= b;
        a->key = K(c->key);
        a->data = T(c->data);
        b->rightSon = c->leftSon;
        b->height = calcHeight(b);
        a->height = calcHeight(a);
        delete (c);
    }

    //preform RR rotation
    //TODO: check correctness
    //TODO: not updated to be rank.
    void rrRotation(Node *a) {
        Node *b = a->rightSon;
        Node *moveA = new Node{
                b->leftSon,
                a->leftSon,
                0,
                K(a->key),
                T(a->data)
        };
        moveA->height = calcHeight(moveA);
        a->leftSon = moveA;
        a->data = T(b->data);
        a->key = K(b->key);
        a->rightSon = b->rightSon;
        a->height = calcHeight(a);
        delete (b);
    }

    //preform RL rotation
    //TODO: not updated to be rank.
    void rlRotation(Node *a) {
        Node *b = a->rightSon;
        Node *c = b->leftSon;
        Node *moveA = new Node{
                c->leftSon,
                a->leftSon,
                0,
                K(a->key),
                T(a->data)
        };
        moveA->height = calcHeight(moveA);
        a->leftSon = moveA;
        a->rightSon= b;
        a->data = T(c->data);
        a->key = K(c->key);
        b->leftSon = c->rightSon;
        b->height = calcHeight(b);
        a->height = calcHeight(a);
        delete (c);

    }

    T& recGetDataByKey(Node *n, const K &key) {

        if (n == NULL)
            throw KeyNotExist();
        if (n->key == key) {
            return n->data;
        } else {
            if (key < n->key) {
                return recGetDataByKey(n->leftSon, key);
            } else {
                return recGetDataByKey(n->rightSon, key);
            }
        }
    }

    int max(int a, int b) {
        return a < b ? b : a;
    }


};

#endif //WET1DATASTRUCTURES_AVLTREE_H
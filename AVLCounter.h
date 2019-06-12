
//
// Created by tsofi on 07/06/2019.
//

#ifndef DATASTRUCTUREWET2_AVLCOUNTER_H
#define DATASTRUCTUREWET2_AVLCOUNTER_H

#include <iostream>

template <class K>
class AVLCounter{
private:
    typedef struct Node_t{
        Node_t *rightSon;
        Node_t *leftSon;
        int height;
        int counter;
        K key;
    }Node;

    Node *root;
    int size;

public:
    AVLCounter() : size(0) {
        root = NULL;
    }

    AVLCounter(const AVLCounter& other){
        recCopy(other.root);
    }


    void inOrderPrint() {
        inOrder(root);
        std::cout << std::endl;
    }

    void insert(const K &key) {
        if (!root) {
            root = new Node{NULL, NULL, 0, 1, K(key)};
            size++;
            return;
        }

        if (!findAndUpdate(key)) {
            Node *n = new Node{NULL, NULL, 0, 1, K(key)};
            recInsert(n, root);
            size++;
        }

    }

    void remove(const K &key) {
        recRemoval(root, NULL, key);
        size--;
    }

    K sumKBestKeys(int k){
        return recSumKBestKeys(root, &k);
    }

    int getSize(){
        return size;
    }

private:
    void recCopy(const Node* n){
        if (n==NULL)
            return;
        insert(n->key);
        recCopy(n->leftSon);
        recCopy(n->rightSon);
    }

    //TODO: check for correctness.
    K recSumKBestKeys(Node* n, int* k){
        if (*k==0 || n==NULL)
            return K();

        K sumB= recSumKBestKeys(n->rightSon, k);
        if (*k!=0){
            (*k)--;
            return sumB+(n->key)+recSumKBestKeys(n->leftSon, k);
        }
        return sumB;
    }

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

    //preform LL rotation
    void llRotation(Node *a) {
        Node *b = a->leftSon;
        Node *moveA = new Node;
        moveA->key = K(a->key);
        moveA->counter = a->counter;
        moveA->rightSon = a->rightSon;
        moveA->leftSon = b->rightSon;
        moveA->height = calcHeight(moveA);
        a->key = K(b->key);
        a->counter = b->counter;
        a->leftSon = b->leftSon;
        a->rightSon = moveA;
        a->height= calcHeight(a);
        delete (b);

    }

    //preform LR rotation
    void lrRotation(Node *a) {
        Node *b = a->leftSon;
        Node *c = b->rightSon;
        Node *moveA = new Node;
        moveA->key = K(a->key);
        moveA->counter = a->counter;
        moveA->rightSon = a->rightSon;
        moveA->leftSon = c->rightSon;
        moveA->height = calcHeight(moveA);
        a->rightSon = moveA;
        a->key = K(c->key);
        a->counter = c->counter;
        b->rightSon = c->leftSon;
        b->height = calcHeight(b);
        a->height = calcHeight(a);
        delete (c);
    }

    //preform RR rotation
    //TODO: check correctness
    void rrRotation(Node *a) {
        Node *b = a->rightSon;
        Node *moveA = new Node;
        moveA->counter = a->counter;
        moveA->key = K(a->key);
        moveA->leftSon = a->leftSon;
        moveA->rightSon = b->leftSon;
        moveA->height = calcHeight(moveA);
        a->leftSon = moveA;
        a->counter = b->counter;
        a->key = K(b->key);
        a->rightSon = b->rightSon;
        a->height = calcHeight(a);
        delete (b);
    }

    //preform RL rotation
    void rlRotation(Node *a) {
        Node *b = a->rightSon;
        Node *c = b->leftSon;
        Node *moveA = new Node;
        moveA->counter = a->counter;
        moveA->key = K(a->key);
        moveA->leftSon = a->leftSon;
        moveA->rightSon = c->leftSon;
        moveA->height = calcHeight(moveA);
        a->leftSon = moveA;
        a->counter = c->counter;
        a->key = K(c->key);
        b->leftSon = c->rightSon;
        b->height = calcHeight(b);
        a->height = calcHeight(a);
        delete (c);

    }

    bool findAndUpdate(const K &key){
        return recFindAndUpdate(key, root);
    }

    bool recFindAndUpdate(const K &key, Node* curr){
        if (curr==NULL)
            return false;

        if (curr->key==key){
            curr->counter++;
            return true;
        }

        if (curr->key>key){
            if (recFindAndUpdate(key, curr->leftSon)){
                return true;
            }

        }

        if (recFindAndUpdate(key, curr->rightSon)){
            return true;
        }

        return false;
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
            delete (temp);
        } else if (n->rightSon == NULL) {
            Node *temp = n->leftSon;
            n->rightSon = temp->rightSon;
            n->leftSon = temp->leftSon;
            n->key = temp->key;
            delete (temp);
        } else {
            Node *temp= findMostLeft(n->rightSon, n);
            n->key = K(temp->key);
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

    int max(int a, int b) {
        return a < b ? b : a;
    }



    void inOrder(Node *root) {
        if (root != NULL) {
            inOrder(root->leftSon);
            for (int i = 0; i < root->counter; ++i) {
                std::cout << root->key<<" ";
            }

            inOrder(root->rightSon);
        }

    }
};


#endif //DATASTRUCTUREWET2_AVLCOUNTER_H


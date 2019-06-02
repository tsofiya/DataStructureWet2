//
// Created by tsofi on 30/05/2019.
//

#ifndef DATASTRUCTUREWET2_AVLRANKCOUNTER_H
#define DATASTRUCTUREWET2_AVLRANKCOUNTER_H

#include <iostream>

template <class T>
class AVLRankCounter{
private:
    typedef struct Node_t{
        Node_t *rightSon;
        Node_t *leftSon;
        int height;
        int rank;
        int counter;
        T key;
    }Node;

    Node *root;
    int size;

public:
    AVLRankCounter() : size(0) {
        root = NULL;
    }


    void inOrderPrint() {
        inOrder(root);
        std::cout << std::endl;
    }

    void insert(const T &data) {
        if (!root) {
            root = new Node{NULL, NULL, 0, 1, 1, T(data)};
            size++;
            return;
        }

        if (!findAndUpdate(data)) {
            Node *n = new Node{NULL, NULL, 0, 1, 1, T(data)};
            recInsert(n, root);
            size++;
        }

    }


private:
    void recInsert(Node *in, Node *curr) {
        curr->rank++;
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
        moveA->key = T(a->key);
        moveA->counter = a->counter;
        moveA->rightSon = a->rightSon;
        moveA->leftSon = b->rightSon;
        moveA->height = calcHeight(moveA);
        moveA->rank = calcRank(moveA);
        a->key = T(b->key);
        a->counter = b->counter;
        a->leftSon = b->leftSon;
        a->rightSon = moveA;
        a->rank=calcRank(a);
        a->height= calcRank(a);
        delete (b);

    }

    //preform LR rotation
    void lrRotation(Node *a) {
        Node *b = a->leftSon;
        Node *c = b->rightSon;
        Node *moveA = new Node;
        moveA->key = T(a->key);
        moveA->counter = a->counter;
        moveA->rightSon = a->rightSon;
        moveA->leftSon = c->rightSon;
        moveA->height = calcHeight(moveA);
        moveA->rank = calcRank(moveA);
        a->rightSon = moveA;
        a->key = T(c->key);
        a->counter = c->counter;
        a->rank = calcRank(c);
        b->rightSon = c->leftSon;
        b->height = calcHeight(b);
        b->rank = calcRank(b);
        a->height = calcHeight(a);
        a->rank = calcRank(a);
        delete (c);
    }

    //preform RR rotation
    //TODO: check correctness
    void rrRotation(Node *a) {
        Node *b = a->rightSon;
        Node *moveA = new Node;
        moveA->rank = a->rank;
        moveA->counter = a->counter;
        moveA->key = T(a->key);
        moveA->leftSon = a->leftSon;
        moveA->rightSon = b->leftSon;
        moveA->height = calcHeight(moveA);
        moveA->rank = calcRank(moveA);
        a->leftSon = moveA;
        a->counter = b->counter;
        a->key = T(b->key);
        a->rightSon = b->rightSon;
        a->height = calcHeight(a);
        a->rank = calcRank(a);
        delete (b);
    }

    //preform RL rotation
    void rlRotation(Node *a) {
        Node *b = a->rightSon;
        Node *c = b->leftSon;
        Node *moveA = new Node;
        moveA->rank = a->rank;
        moveA->counter = a->counter;
        moveA->key = T(a->key);
        moveA->leftSon = a->leftSon;
        moveA->rightSon = c->leftSon;
        moveA->height = calcHeight(moveA);
        moveA->rank = calcRank(moveA);
        a->leftSon = moveA;
        a->counter = c->counter;
        a->key = T(c->key);
        a->rank = calcRank(a);
        b->leftSon = c->rightSon;
        b->height = calcHeight(b);
        b->rank = calcRank(b);
        a->height = calcHeight(a);
        a->rank = calcRank(a);
        delete (c);

    }

    bool findAndUpdate(const T &data){
        return recFindAndUpdate(data, root);
    }

    bool recFindAndUpdate(const T &data, Node* curr){
        if (curr==NULL)
            return false;

        if (curr->key==data){
            curr->counter++;
            curr->rank++;
            return true;
        }

        if (curr->key>data){
            if (recFindAndUpdate(data, curr->leftSon)){
                curr->rank++;
                return true;
            }

        }

        if (recFindAndUpdate(data, curr->rightSon)){
            curr->rank++;
            return true;
        }
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

    int calcRank(Node *n) {
        if (n->rightSon == NULL && n->leftSon == NULL)
            return n->counter;
        if (n->rightSon == NULL)
            return n->counter + n->leftSon->rank;
        if (n->leftSon == NULL)
            return n->counter + n->rightSon->rank;
        return n->counter + n->leftSon->rank+ n->rightSon->rank;
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


#endif //DATASTRUCTUREWET2_AVLRANKCOUNTER_H

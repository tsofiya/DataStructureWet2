//
// Created by lucio on 6/9/2019.
//

#ifndef WET2_LIST_H
#define WET2_LIST_H


#include "Wet2Exceptions.h"
#include <istream>
#include <iostream>

using std::ostream;

template<class T>
class List {
public:
    struct Node {
        T data;
        Node *next;
    };

    //friend ListIterator;
    class ListIterator {
    private:
        List *list;
        Node *current;
    public:
        ListIterator(List *lst) : list(lst) {
            if (lst == NULL)
                throw InvalidInput();
            if (lst->head == NULL) {
                current = NULL;
            }
            current = (lst)->head;
        }

        ListIterator &operator++() {
            if (current == NULL)
                return *this;
            current = current->next;
            return *this;
        }


        Node *getCurrent() {
            return current;
        }

        T &operator*() {
            return current->data;
        }

        bool isEnd() {
            return current == NULL;
        }


    };

private:
    Node *head;

public:

    List() {
        head = NULL;
    }

    Node *push(const T &data) {
        Node * temp = new Node{data, head};
        head= temp;
        return head;

    }

    /*
       Node *push(const T &data) {
           Node *n = new Node;
           n->data = data;
           n->previous=NULL;
           n->next=head;
           if (head){
               head->previous=n;
           }
           head=n;
           return n;

       }

   */
    /*
       Node *removeNode(const Node *toRemove) {

           if (toRemove == NULL) {
               return NULL; //or throw exception?
           }
           if (toRemove->next) {
               if (toRemove->previous) {
                   (toRemove->next)->previous = toRemove->previous;
                   (toRemove->previous)->next = toRemove->next;
                   delete (toRemove);
                   return head;
               } else {
                   head = toRemove->next;
                   head->previous = NULL;
                   delete (toRemove);
                   return head;
               }
           }
           if (!toRemove->next) {
               if (toRemove->previous) {
                   tail = (toRemove->previous);
                   tail->next = NULL;
                   delete (toRemove);
                   return head;
               } else { //if (!toRemove->previous)
                   delete (toRemove);
                   head = NULL;
                   tail = NULL;
                   return NULL;
               }
           }
           return head;
       }

   */

    void removeNode(Node *toRemove) {

        if (head == toRemove) {
            head = head->next;
            delete (toRemove);
            return;
        }

        Node* curr= head;
        Node* prev= head->next;
        while(prev->next!= NULL){
            if (prev==toRemove)
            {
                delete (prev);
                curr->next=NULL;
            }
            curr= prev;
            prev= prev->next;
        }
    }

    friend ostream &operator<<(ostream &os, List<T> &list) {
        //os << "direction 1: " << std::endl;
        os << "BEGIN <-> ";
        Node *ptr = list.head;
        while (ptr != NULL) {
            os << ptr->data << " <-> ";
            ptr = ptr->next;
        }
        os << "END";
        return os;
    }


    ~List() {
        Node *currentPos = this->head;
        while (currentPos) {
            Node *nextPos = currentPos->next;
            delete (currentPos);
            currentPos = nextPos;
        }
    }

    Node *getHead() {
        return head;
    }

/*
    //I made the two following function return ListIterators, not referenecs... hope it'll do, if not- flip back to &s
    ListIterator beginForward() {
        return ListIterator(this, true);
    }

    ListIterator beginBackward() {
        return ListIterator(this, false);
    }
*/
    int size() {
        int s = 0;
        Node *ptr = head;
        while (ptr != NULL) {
            s++;
            ptr = ptr->next;
        }
        return s;
    }

};


#endif //WET2_LIST_H

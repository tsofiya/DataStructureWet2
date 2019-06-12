
#ifndef WET2_BIDIRECTIONALLIST_H
#define WET2_BIDIRECTIONALLIST_H

#include "Wet2Exceptions.h"
#include "DynamicArrayExceptions.h"
#include <istream>

using std::ostream;

template<class T>
class BiDirectionalList {
public:
    class Node{
    public:
        T data;
        Node *next;
        Node *previous;
    };

    Node *head;
    Node *tail;
    //friend ListIterator;

public:

    class ListIterator {
    private:
        BiDirectionalList *list;
        Node *current;
    public:
        ListIterator(BiDirectionalList *lst, bool hOrT) : list(lst) {
            if (lst == NULL)
                throw NullArgument();
            if (lst->head == NULL)
                current = NULL;
            else if (hOrT) {
                current = (lst)->head;
            } else {
                current = (lst)->tail;
            }
        }

        ListIterator &operator++() {
            if (current == NULL)
                return *this;
            current = current->next;
            return *this;
        }

        ListIterator &operator--() {
            if (current == NULL)
                return *this;
            current = current->previous;
            return *this;
        }

        Node* getCurrent(){
            return current;
        }

        T &operator*() {
            return current->data;
        }

        bool isEnd(){
            return current==NULL;
        }


    };

    BiDirectionalList(Node*h = NULL, Node *t = NULL) : head(h), tail(t) {}

    Node *push(const T &data) {
        Node *n = new Node{data, NULL, NULL};
        n->data = data;
        if (head == NULL) {
            tail = n;
            head = n;
            n->next = NULL;
            n->previous = NULL;
        } else {
            head->previous=n;
            n->next = head;
            n->previous = NULL;
            head = n;
        }
        return n;

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

 Node *removeNode( Node *toRemove) {
     if (toRemove == NULL){
         return head;
     }

     if (toRemove->previous == NULL){
         head=(toRemove->next);
     }
     if (toRemove->next!=NULL){
         toRemove->next->previous=toRemove->previous;
     }
     if (toRemove->previous!=NULL){
         toRemove->previous->next = toRemove->next;
     }
     delete(toRemove);
    return head;
 }

    friend ostream &operator<<(ostream &os, BiDirectionalList<T> &list) {
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


    ~BiDirectionalList() {
        Node *currentPos = this->head;
        while (currentPos) {
            Node *nextPos = currentPos->next;
            delete (currentPos);
            currentPos = nextPos;
        }
    }

    Node* getHead(){
        return head;
    }

    //I made the two following function return ListIterators, not referenecs... hope it'll do, if not- flip back to &s
    ListIterator beginForward() {
        return ListIterator(this, true);
    }

    ListIterator beginBackward() {
        return ListIterator(this, false);
    }

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

#endif
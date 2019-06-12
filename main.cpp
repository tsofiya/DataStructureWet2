#include "testclass.cpp"
#include <list>
#include <assert.h>

#ifndef HW_WET2_PROJECT_ROOMSHASHTRY_H
#define HW_WET2_PROJECT_ROOMSHASHTRY_H

#include <stddef.h>
#include <math.h>
#include <iostream>

using namespace std;


#endif //HW_WET2_PROJECT_ROOMSHASHTRY_H

void test1(int testlines);
void test2(int testlines);
void test3(int testlines);
void test4(int testlines);
template <class T>
class uselesslist{

public:

    T data;
    uselesslist* next;

    explicit uselesslist(T t){

        data = t;
        next = nullptr;

    }


};

void TestThisMF(int testlines){


    if(0>=testlines) {
        cout << "Don't be a jerk...";
        int* x = nullptr;
        *x = testlines;
    }

    test1(testlines);
    test2(testlines);
    test3(testlines);
    //   test4(testlines);


}

void test1(int testlines){

    srand ((unsigned int)time(nullptr));

    test* t = t->init(rand()%150+1);

    for(int i=0; i<testlines; i++){

        int x = rand()%7;

        if(x==0)
            t->getaveragestudentsincourse(rand() % 150 - 15, rand() % 20 + 1);

        if(x==1)
            t->competition(rand() % 150 - 15, rand() % 150 - 15,rand() % 150 - 15);

        if(x==2)
            t->mergecourses(rand() % 150 - 15, rand() % 150 - 15);

        if(x==3)
            t->deletelecture(rand() % 150 - 15, rand()%20+1);

        if(x==4)
            t->addlecture(rand()%150 - 15,rand()%150 - 15,rand()%150 - 15,rand()%20+1,rand()%150 - 15);


        if(x==5)
            t->deleteroom(rand()%150 - 15);

        if(x==6)
            t->addroom(rand()%150 - 15);


    }


}


void test2(int testlines){

    srand ((unsigned int)time(nullptr));

    test* t = t->init(50);

    for(int i=0; i<testlines; i++){

        int x = rand()%3;

        if(x==0)
            t->getaveragestudentsincourse(rand() % 50 - 5, rand()% 10 + 1);

        if(x==1)
            t->competition(rand()%51, rand() %51,rand() %150);

        if(x==2)
            t->mergecourses(rand() % 80+1, rand() % 80 +1);

        if(x==3)
            t->deletelecture(rand() % 50, rand()%10+1);

        if(x==4 || x==10 || x==11 || x==12)
            t->addlecture(rand()%50,rand()%50,rand()%50,rand()%11,rand()%50);


        if(x==5 || x==7)
            t->deleteroom(rand()%50);

        if(x==6 || x==8 || x==9)
            t->addroom(rand()%50);


    }


}

void test3(int testlines){

    srand ((unsigned int)time(nullptr));

    test* t = t->init(135);

    for(int i=0; i<testlines; i++){


        int x = rand()%7;

        if(x==0)
            t->getaveragestudentsincourse(rand() % 150 - 15, rand() % 20 + 1);

        if(x==1)
            t->competition(rand() % 150 - 15, rand() % 150 - 15,rand() % 150 - 15);


        if(x==4 || x==3)
            t->addlecture(rand()%150 - 15,rand()%150 - 15,rand()%150 - 15,rand()%20+1,rand()%150 - 15);


        if(x==6 || x==2 || x==5)
            t->addroom(rand()%150 - 15);


    }

}

void test4(int testlines){

    srand ((unsigned int)time(nullptr));

    test* t = t->init(1000-15);

    cout<<"\n";
    cout<<"Almost done";
    cout<<"\n";

    for(int i=0; i<testlines; i++){

        cout<<i;
        cout<<" ";

        int x = rand()%7;

        if(x==0)
            t->getaveragestudentsincourse(rand() % 1000 - 15, rand() % 20 + 1);

        if(x==1)
            t->competition(rand() % 1000 - 15, rand() % 1000 - 15,rand() % 150 - 15);

        if(x==2)
            t->mergecourses(rand() % 1000 - 15, rand() % 1000 - 15);

        if(x==3)
            t->deletelecture(rand() % 1000 - 15, rand()%20+1);

        if(x==4)
            t->addlecture(rand()%1000 - 15,rand()%1000 - 15,rand()%1000 - 15,rand()%20+1,rand()%1000 - 15);


        if(x==5)
            t->deleteroom(rand()%1000 - 15);

        if(x==6)
            t->addroom(rand()%1000 - 15);


    }


}






int main(){
    TestThisMF(1000000); //good example

    // TestThisMF(-9); //  bad example


    cout<<"done";

    return 0;
}

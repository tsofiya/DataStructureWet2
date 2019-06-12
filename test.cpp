#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "library2.h"


void Test_Init_And_Quit(){
    void* DS = Init(-1);
    assert(DS == nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    DS = Init(0);
    assert(DS == nullptr);
    Quit(&DS);
    DS = Init(40);
    assert(DS != nullptr);
    Quit(&DS);
    DS = Init(1000);
    assert(DS != nullptr);
    Quit(&DS);
}
void Sagal_Test(){
    float avrage=0;
    void* DS = Init(2);
    assert(DS != nullptr);
    assert(addRoom(DS,5)==SUCCESS);
    assert(addRoom(DS,10)==SUCCESS);
    assert(deleteRoom(DS,10)==SUCCESS);
    assert(addLecture(DS,2,1,10,2,5)==FAILURE);
    assert(addLecture(DS,1,5,5,1,30)==SUCCESS);
    assert(addLecture(DS,2,3,5,2,20)==SUCCESS);
    assert(addRoom(DS,6)==SUCCESS);
    assert(addLecture(DS,2,1,6,5,5)==SUCCESS);
    assert(deleteLecture(DS,5,6)==SUCCESS);
    assert(mergeCourses(DS,1,2)==SUCCESS);
    assert(getAverageStudentsInCourse(DS,2,5,&avrage)==SUCCESS);
    assert(avrage==25);
    assert(getAverageStudentsInCourse(DS,1,5,&avrage)==SUCCESS);
    assert(avrage==25);
    Quit(&DS);
}

void Test_AddLecture(){

    void* DS = Init(5);
    assert(DS != nullptr);
    assert(addRoom(DS,5)==SUCCESS);
    assert(addRoom(DS,10)==SUCCESS);
    assert(addRoom(DS,12)==SUCCESS);
    assert(addRoom(DS,13)==SUCCESS);
    assert(addRoom(DS,2)==SUCCESS);
    assert(addRoom(DS,8)==SUCCESS);
    assert(addRoom(DS,7)==SUCCESS);
    assert(addRoom(DS,1)==SUCCESS);
    assert(addRoom(DS,11)==SUCCESS);
    assert(addRoom(DS,1)==FAILURE);
    assert(deleteRoom(DS,10)==SUCCESS);
    assert(deleteRoom(DS,11)==SUCCESS);
    assert(deleteRoom(DS,1)==SUCCESS);

    assert(addLecture(DS,2,1,10,2,5)==FAILURE);
    assert(addLecture(DS,2,1,1,2,5)==FAILURE);
    assert(addLecture(DS,2,1,11,2,5)==FAILURE);

    assert(addLecture(DS,1,5,5,1,30)==SUCCESS);
    assert(addLecture(DS,2,5,5,7,0)==SUCCESS);
    assert(addLecture(DS,2,5,5,1,-2)==INVALID_INPUT);
    assert(addLecture(DS,2,5,5,12,30)==INVALID_INPUT);
    assert(addLecture(DS,2,5,0,1,30)==INVALID_INPUT);
    assert(addLecture(DS,9,5,0,1,30)==INVALID_INPUT);
    assert(addLecture(DS,9,-1,0,1,30)==INVALID_INPUT);

    assert(addLecture(DS,1,5,2,1,25)==FAILURE);
    assert(addLecture(DS,1,5,2,1,10)==FAILURE);

    assert(addLecture(DS,2,3,5,2,20)==SUCCESS);
    assert(addLecture(DS,1,2,5,2,10)==FAILURE);
    assert(addLecture(DS,1,5,5,2,10)==FAILURE);
    assert(addLecture(DS,4,5,5,1,7)==FAILURE);
    assert(addLecture(DS,4,1,13,7,7)==SUCCESS);
    assert(addLecture(DS,4,1,13,7,7)==FAILURE);
    assert(addLecture(DS,4,1,12,7,7)==FAILURE);
    assert(addLecture(DS,4,7,8,6,7)==SUCCESS);
    assert(addLecture(DS,3,5,8,6,5)==FAILURE);
    assert(addLecture(DS,3,5,8,4,9)==SUCCESS);
    assert(addLecture(DS,4,7,12,5,43)==SUCCESS);
    assert(addLecture(DS,3,2,12,2,14)==SUCCESS);
    assert(addLecture(DS,3,41,12,3,5)==SUCCESS);
    assert(addLecture(DS,3,42,12,4,5)==SUCCESS);
    assert(addLecture(DS,2,8,13,9,12)==SUCCESS);

    Quit(&DS);
}

void Test_DeleteLecture(){
    void* DS = Init(20);
    assert(DS != nullptr);
    for(int i=1;i<=20;i++)
    {
        addRoom(DS,i);
    }
    assert(addLecture(DS,2,1,10,1,5)==SUCCESS);
    assert(addLecture(DS,2,1,10,2,5)==SUCCESS);
    assert(addLecture(DS,2,1,10,3,5)==SUCCESS);
    assert(addLecture(DS,2,1,10,4,10)==SUCCESS);
    assert(addLecture(DS,2,1,10,5,10)==SUCCESS);
    assert(addLecture(DS,2,3,9,3,5)==SUCCESS);
    assert(addLecture(DS,2,3,9,4,10)==SUCCESS);
    assert(addLecture(DS,2,3,9,5,10)==SUCCESS);
    assert(deleteLecture(DS,11,10)==INVALID_INPUT);
    assert(deleteLecture(nullptr,11,10)==INVALID_INPUT);
    assert(deleteLecture(DS,5,0)==INVALID_INPUT);
    assert(deleteLecture(DS,4,21)==FAILURE);
    assert(deleteLecture(DS,4,19)==FAILURE);
    assert(deleteRoom(DS,10)==FAILURE);
    for(int i=1;i<=4;i++)
    {
        assert(deleteLecture(DS,i,10)==SUCCESS);
    }
    assert(deleteRoom(DS,10)==FAILURE);
    assert(deleteLecture(DS,5,10)==SUCCESS);
    assert(deleteRoom(DS,10)==SUCCESS);
    assert(deleteLecture(DS,4,10)==FAILURE);
    addRoom(DS,21);
    for(int i=1;i<=5;i++)
    {
        assert(addLecture(DS,9,1,21,i,i+5)==SUCCESS);
    }
    Quit(&DS);
}
void Test_merge_courses(){

    void* DS = Init(20);
    assert(DS != nullptr);
    for(int i=1;i<=20;i++)
    {
        addRoom(DS,i);
    }

    for (int j = 1; j < 7; j++) {
        assert(addLecture(DS,2,1,1,j,5+j)==SUCCESS);
        assert(addLecture(DS,2,4,2,j,4+j)==SUCCESS);
    }

    for (int j = 7; j <= 10; j++) {
        assert(addLecture(DS,3,1,3,j,5+j)==SUCCESS);
        assert(addLecture(DS,3,4,2,j,4+j)==SUCCESS);
         }

    assert(mergeCourses(DS,21,3)==INVALID_INPUT);
    assert(mergeCourses(DS,2,0)==INVALID_INPUT);
    assert(mergeCourses(nullptr,2,3)==INVALID_INPUT);

    assert(addLecture(DS,3,1,3,2,5)==SUCCESS);
    assert(mergeCourses(DS,2,3)==FAILURE);
    assert(deleteLecture(DS,2,3)==SUCCESS);
    assert(mergeCourses(DS,2,3)==SUCCESS);
    assert(mergeCourses(DS,2,3)==FAILURE);
    assert(addLecture(DS,3,1,3,7,12)==FAILURE);
    assert(addLecture(DS,2,4,2,1,5)==FAILURE);

    for (int j = 1; j < 7; j++) {
        assert(addLecture(DS,4,2,6,j,5+j)==SUCCESS);
        assert(addLecture(DS,4,3,7,j,4+j)==SUCCESS);
    }

    for (int j = 7; j <= 10; j++) {
        assert(addLecture(DS,5,2,6,j,5+j)==SUCCESS);
        assert(addLecture(DS,5,3,7,j,4+j)==SUCCESS);
    }
    assert(mergeCourses(DS,4,5)==SUCCESS);
    assert(addLecture(DS,4,1,8,3,9)==SUCCESS);
    assert(mergeCourses(DS,4,3)==FAILURE);
    assert(deleteLecture(DS,3,8)==SUCCESS);
    assert(mergeCourses(DS,2,5)==SUCCESS);
    assert(mergeCourses(DS,5,3)==FAILURE);
    assert(addLecture(DS,5,1,8,7,12)==FAILURE);

    for(int i=40;i<=400;i++)
    {
        addRoom(DS,i);
    }
    for(int i=40;i<150;i++){
        for(int j=1;j<=10;j++){
            if(j<=5)
            assert(addLecture(DS,6,i,i,j,i+j)==SUCCESS);
            else
                assert(addLecture(DS,6,i,i,j,i)==SUCCESS);
        }
    }
    for(int i=150;i<300;i++){
        for(int j=1;j<=10;j++){
            if(j<=5)
            assert(addLecture(DS,7,i,i,j,i+j)==SUCCESS);
            else
                assert(addLecture(DS,7,i,i,j,i)==SUCCESS);
        }
    }
    assert(mergeCourses(DS,6,7)==SUCCESS);
    for(int i=300;i<400;i++) {
        assert(addLecture(DS, 7, i, i,4 , i / 5) == SUCCESS);
    }
    Quit(&DS);
}
void Test_competition_And_Average(){
    void* DS = Init(20);
    assert(DS != nullptr);
    int winner=0;
    int x=0;
    int y=0;
    float average;
    float check;
    float check2=0;
    float check3=0;
    for(int i=1;i<=301;i++)
    {
        addRoom(DS,i);
    }
    for(int i=1;i<200;i++){
        for(int j=1;j<=10;j++){
            if(j<=5) {
                assert(addLecture(DS, 6, i, i, j, i + j) == SUCCESS);
                x+=i+j;
            }
            else {
                assert(addLecture(DS, 6, i, i, j, i) == SUCCESS);
                x+=i;
            }

           y++;
        }
    }
    check=(float)x / y;
    assert(getAverageStudentsInCourse(DS,1,1,&average)== SUCCESS);
    assert(average==check);
    deleteLecture(DS,1,1);
    x-=2;
    y--;
    check=(float)x / y;
    check2+=x;
    check3+=y;
    assert(getAverageStudentsInCourse(DS,1,1,&average)== FAILURE);
    assert(getAverageStudentsInCourse(DS,2,1,&average)== SUCCESS);
    assert(average==check);
    assert(getAverageStudentsInCourse(nullptr,1,1,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,20,1,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,1,0,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,0,5,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,2,500,&average)== FAILURE);
    assert(getAverageStudentsInCourse(DS,2,301,&average)== FAILURE);
    x=0;
    y=0;
    for(int i=200;i<300;i++){
        for(int j=1;j<=10;j++){
            if(j<=5){
                assert(addLecture(DS,7,i,i,j,i+j)==SUCCESS);
                x+=i+j;
            }
            else {
                assert(addLecture(DS, 7, i, i, j, i) == SUCCESS);
                x+=i;
            }
            y++;
        }
    }
    check=(float)x / y;
    check2+=x;
    check3+=y;
    assert(getAverageStudentsInCourse(DS,1,200,&average)== SUCCESS);
    assert(average==check);
    assert(competition(DS,6,22,8,&winner)==INVALID_INPUT);
    assert(competition(DS,32,7,6,&winner)==INVALID_INPUT);
    assert(competition(nullptr,6,7,5,&winner)==INVALID_INPUT);
    assert(competition(nullptr,0,7,6,&winner)==INVALID_INPUT);
    assert(competition(nullptr,6,0,6,&winner)==INVALID_INPUT);
    assert(competition(nullptr,6,7,0,&winner)==INVALID_INPUT);
    for(int i=1;i<500;i++){
        assert(competition(DS,6,7,i,&winner)==SUCCESS);
        assert(winner==7);
    }
    assert(mergeCourses(DS,6,7)==SUCCESS);
    check= (float)check2/ check3;
    assert(getAverageStudentsInCourse(DS,1,200,&average)== SUCCESS);
    assert(average==check);
    assert(competition(DS,6,7,8,&winner)==FAILURE);
    Quit(&DS);

}
void Final_test(){
    void* DS = Init(20);
    assert(DS != nullptr);
    for(int i=1;i<=20;i++)
    {
        addRoom(DS,i);
    }
    assert(addLecture(DS,1,5,5,1,30)==SUCCESS);
    assert(addLecture(DS,2,3,5,2,20)==SUCCESS);
    assert(addLecture(DS,4,1,13,7,7)==SUCCESS);
    assert(addLecture(DS,4,7,8,6,7)==SUCCESS);
    assert(addLecture(DS,3,5,8,4,9)==SUCCESS);
    assert(addLecture(DS,4,7,12,5,43)==SUCCESS);
    assert(addLecture(DS,3,2,12,2,14)==SUCCESS);
    assert(addLecture(DS,3,41,12,3,5)==SUCCESS);
    assert(addLecture(DS,3,42,12,4,5)==SUCCESS);
    assert(addLecture(DS,2,8,13,9,12)==SUCCESS);
    int winner=0;
    competition(DS,4,2,2,&winner);
    assert(winner==4);
    competition(DS,3,2,3,&winner);
    assert(winner==2);
    competition(DS,3,2,4,&winner);
    assert(winner==3);
    competition(DS,3,2,3,&winner);
    assert(winner==2);
    deleteLecture(DS,13,12);
    competition(DS,3,2,4,&winner);
    assert(winner==3);
    assert(addLecture(DS,4,19,16,7,3)==SUCCESS);
    assert(mergeCourses(DS,3,2)==SUCCESS);
    competition(DS,3,4,5,&winner);
    assert(winner==4);
    assert(mergeCourses(DS,1,2)==SUCCESS);
    competition(DS,3,4,5,&winner);
    assert(winner==3);
    assert(competition(DS,1,3,5,&winner)==FAILURE);
    Quit(&DS);
}




int main(int argc, const char**argv) {

    cout << "Welcome to the tests for wet2" << endl;
    cout << " Good Luck." << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;

    cout << "Testing sagal_test" << endl;
    Sagal_Test();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing Init And Quit" << endl;
    Test_Init_And_Quit();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing AddLecture" << endl;
    Test_AddLecture();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing DeleteLecture" << endl;
    Test_DeleteLecture();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing merge_courses" << endl;
    Test_merge_courses();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing competition_And_Average" << endl;
    Test_competition_And_Average();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "FINAL TEST!!" << endl;
    Final_test();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;



    cout << "well done! you did it!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;


    return 0;
}
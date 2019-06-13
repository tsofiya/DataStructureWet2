//
// Created by tsofi on 06/06/2019.
//

#ifndef DATASTRUCTUREWET2_SCHEDULE2_H
#define DATASTRUCTUREWET2_SCHEDULE2_H
#define HOURS 10

#include "AVLtree.h"
#include "UnionFind.h"
#include "Wet2Exceptions.h"
#include "HashTable.h"
#include "AVLCounter.h"

using namespace Wet2Utils;

class Schedule2 {
    class LectureGroup {
        friend Schedule2;
        bool inHour[HOURS];
        int studentsPerLecture[HOURS];
        //int students;
        int rooms[HOURS];
    public:
        LectureGroup()  {
            for (int i = 0; i <HOURS ; ++i) {
                studentsPerLecture[i]=0;
                inHour[i]= false;
                rooms[i]= 0;
            }

        }

        LectureGroup(const LectureGroup &other) {
            for (int i = 0; i < HOURS; ++i) {
                studentsPerLecture[i]=other.studentsPerLecture[i];
                inHour[i]= other.inHour[i];
                rooms[i]= other.rooms[i];
            }
        }

        void addLecture(int hour, int room) {
            hour--;
            //TODO- check in hash if the room is available! this is done outside, not here.
            if (hour < 0 || hour > HOURS || room <= 0) //todo: what if it is equal to hours? that can happen and its a problem...
                throw InvalidInput();
            if (inHour[hour])
                throw Failure();
            inHour[hour] = true;
            rooms[hour] = room;
        }

        void deleteLecture(int hour, int room) {
            hour--;
            if (hour < 0 || hour > HOURS || room <= 0)
                throw InvalidInput();
            inHour[hour] = false;
            rooms[hour] = 0;

        }

        LectureGroup operator+(const LectureGroup &other) {
            LectureGroup group(other);
            for (int i = 0; i < HOURS; ++i) {
                if (inHour[i] && other.inHour[i])
                    throw Failure();
                if (inHour[i]) {
                    group.inHour[i] = true;
                    group.rooms[i] = rooms[i];
                    group.studentsPerLecture[i]=studentsPerLecture[i];

                } else if (other.inHour[i]) {
                    group.inHour[i] = true;
                    group.rooms[i] = other.rooms[i];
                    group.studentsPerLecture[i]=other.studentsPerLecture[i];

                } else
                    group.inHour[i] = false;
            }
            return group;
        }


    };

    class CourseID {
        friend Schedule2;
        int numStudent;
        //int numStudentsPerLecture[HOURS];
        int numCourse;
        int numLectures;
        AVLtree<int, LectureGroup> lectures;
        AVLCounter<int> bestGroups;


    public:
        CourseID(int id) :
                           numStudent(0), numCourse(id), numLectures(0),  lectures(), bestGroups() {

        }
        CourseID() :
                numStudent(0), numCourse(0), numLectures(0), lectures(), bestGroups() {

        }
        CourseID(const CourseID& other) :
                                           numStudent(other.numStudent), numCourse(other.numCourse), numLectures(other.numLectures),lectures(other.lectures), bestGroups(other.bestGroups) {

        }

        ~CourseID() {}

        CourseID &operator+=(CourseID &other) {

        //    AVLtree<int, LectureGroup> lec(lectures.mergeTrees(other.lectures));
            lectures=lectures.mergeTrees(other.lectures);
            bestGroups= bestGroups.mergeTrees(other.bestGroups);
            //bestGroups= best;

            numStudent+=other.numStudent;

            numLectures+=other.numLectures;
            return *this;
        }

    };

    class IntArray {
        int *arr;
        int * data;
        int size;
        friend Schedule2;

    public:
        IntArray(int s):size(s) {
            arr = new int[size];
            data = new int[size];
            for (int i = 0; i < size; ++i) {
                arr[i] = 0;
                data[i] = 0;
            }
        }

        IntArray(const IntArray &other) {
            arr = new int[other.size];
            data = new int[other.size];
            size= other.size;
            for (int i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
                data[i] = other.data[i];
            }
        }


        int *operator[](int i) {
            return arr + i;
        }

        ~IntArray() {
            delete[] arr;
            delete[] data;
        }
    };


    HashTable<IntArray> roomsHash;
    UnionFind<CourseID> courses;
    int coursesNum;

public:

    Schedule2(int n) : roomsHash(100), courses(n), coursesNum(n) {

    }//here we must insert dummy nodes into the roomHahs table's Lists

    void addRoom(int roomId) {
        if (roomId <= 0)
            throw InvalidInput();
        if (roomsHash.member(roomId)){
            throw Failure();
        }
        roomsHash.insert(roomId, IntArray(10));
    }

    void deleteRoom(int roomId) {
        if (roomId <= 0)
            throw InvalidInput();
        if (!roomsHash.member(roomId))
            throw Failure();
        int* arr = roomsHash.getDataByKey(roomId).arr;
        for (int i = 0; i < HOURS; ++i) {
            if (arr[i])
                throw Failure();
        }

        roomsHash.deleteElement(roomId);
    }

    void addLecture(int courseID, int groupID, int roomID, int hour, int numStudents) {
        if (courseID < 1 || courseID > coursesNum || roomID <= 0
            || numStudents < 0 || hour < 1 || hour > HOURS || groupID < 0)
            throw InvalidInput();
        if (!roomsHash.member(roomID))
            throw Failure();
        int* arr = roomsHash.getDataByKey(roomID).arr;
        int* data = roomsHash.getDataByKey(roomID).data;
        if (arr[hour - 1])
            throw Failure();

        //CourseID id = courses.Find(courseID - 1);
        //courses.Find(courseID - 1).numStudent+=numStudents;

        if (courses.Find(courseID - 1).lectures.elementExistsByKey(groupID)){
            if( courses.Find(courseID - 1).lectures.getDataByKey(groupID).inHour[hour-1])
                throw Failure();
        }
        else {
            courses.Find(courseID - 1).lectures.insert(groupID, LectureGroup());

        }
        courses.Find(courseID - 1).lectures.getDataByKey(groupID).inHour[hour-1]= true;
        courses.Find(courseID - 1).lectures.getDataByKey(groupID).rooms[hour-1]= roomID;
        courses.Find(courseID-1).lectures.getDataByKey(groupID).studentsPerLecture[hour-1]=numStudents;
        courses.Find(courseID-1).numStudent+=numStudents;
        courses.Find(courseID - 1).bestGroups.insert(numStudents);
        courses.Find(courseID - 1).numLectures++;
        arr[hour - 1] = courseID;
        data[hour-1]= groupID;
    }

    void deleteLecture(int hour, int roomID){
        if (hour<1 || hour>10 || roomID<=0)
            throw InvalidInput();
        if (!roomsHash.member(roomID))
            throw Failure();
        //  IntArray array= roomsHash.getDataByKey(roomID);
        int* arr = roomsHash.getDataByKey(roomID).arr;
        int* data = roomsHash.getDataByKey(roomID).data;

        if (!arr[hour-1])
            throw Failure();
        int courseID= (arr[hour-1]);

        //CourseID c= courses.Find(courseID);
        int groupID= data[hour-1];

        //  LectureGroup l= courses.Find(courseID).lectures.getDataByKey(groupID);
        courses.Find(courseID-1).lectures.getDataByKey(groupID).inHour[hour-1]= false;
        courses.Find(courseID-1).lectures.getDataByKey(groupID).rooms[hour-1]= 0;
        courses.Find(courseID-1).numStudent-=courses.Find(courseID-1).lectures.getDataByKey(groupID).studentsPerLecture[hour-1];
        courses.Find(courseID-1).bestGroups.remove(courses.Find(courseID-1).lectures.getDataByKey(groupID).studentsPerLecture[hour-1]);
        courses.Find(courseID-1).lectures.getDataByKey(groupID).studentsPerLecture[hour-1]=0;
        courses.Find(courseID - 1).numLectures--;
        (arr[hour-1])= 0;
        data[hour-1]= 0;
   //     for (int i = 0; i < HOURS; ++i) {
    //        if (courses.Find(courseID-1).lectures.getDataByKey(groupID).inHour[i])
      //          return;
      //  }

//        int students= courses.Find(courseID-1).lectures.getDataByKey(groupID).students;
//        courses.Find(courseID-1).numStudentsPerLecture[hour-1]=0;
//        courses.Find(courseID-1).bestGroups.remove(students);
//        courses.Find(courseID-1).lectures.remove(groupID);


    }

    void  mergeCourses(int courseID1, int courseID2){
        if (courseID1>coursesNum || courseID2>coursesNum|| courseID1<1 || courseID2<1)
            throw InvalidInput();

        if (courseID1 == courseID2){
            throw Failure();
        }
        if (courses.checkEqual((courseID1-1), (courseID2-1))){
            throw Failure();
        }
        courseID1--;
        courseID2--;
        courses.Union(courseID1, courseID2);
    }

    int competition (int courseID1, int courseID2, int numGroups){

        if (courseID1< 1 || courseID2 < 1 || numGroups < 1 || courseID1 > coursesNum || courseID2 > coursesNum){
            throw InvalidInput();
        }
        if (courseID1 == courseID2){
            throw Failure();
        }
        if (courses.checkEqual((courseID1-1), (courseID2-1))){
            throw Failure();
        }
      //  CourseID id1 = courses.Find(courseID1 - 1);
       // CourseID id2 = courses.Find(courseID2 - 1); //todo: what if we didnt find them...?
        int studentSumInBest1;
        int studentSumInBest2;

        studentSumInBest1 = courses.Find(courseID1 - 1).bestGroups.sumKBestKeys(numGroups);
//        if (courses.Find(courseID1 - 1).bestGroups.getSize() >= numGroups){
//
//        }
//        else{
//            studentSumInBest1 = courses.Find(courseID1 - 1).bestGroups.sumKBestKeys(courses.Find(courseID1 - 1).bestGroups.getSize());
//
//        }
        studentSumInBest2 = courses.Find(courseID2 - 1).bestGroups.sumKBestKeys(numGroups);
//        if (courses.Find(courseID2 - 1).bestGroups.getSize() >= numGroups){
//
//        }
//        else{
//            studentSumInBest2 = courses.Find(courseID2 - 1).bestGroups.sumKBestKeys(courses.Find(courseID2 - 1).bestGroups.getSize());
//        }
        if (studentSumInBest1 > studentSumInBest2){
            return courseID1;
        }
        if (studentSumInBest1 < studentSumInBest2){
            return courseID2;
        }
        if (courseID1 > courseID2){
            return courseID1;
        }
        return courseID2;
    }

    float getAverageStudentsInCourse (int hour, int roomID){

        if (hour < 1 || hour > HOURS || roomID <=0){
            throw InvalidInput();
        }
        if (!roomsHash.member(roomID)){
            throw Failure();
        }
        int* hourArray = roomsHash.getDataByKey(roomID).arr;
        if (hourArray[hour-1] == 0){
            throw Failure();
        }
        int courseID = (hourArray[hour-1]);
        //this should never happen, but just in case.....
        if ( courses.Find(courseID - 1).lectures.getTreeSize() == 0 ){
            throw Failure();
        }
        float total =0;
      //  for (int i=0; i<HOURS; i++){
           total=courses.Find(courseID - 1).numStudent;
        //}
        float average = ((total)/((float )( courses.Find(courseID - 1).numLectures)));
        return average;
    }

};



#endif //DATASTRUCTUREWET2_SCHEDULE2_H
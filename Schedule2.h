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
        int students;
        int rooms[HOURS];
    public:
        LectureGroup(int s, int hour, int room) : students(s) {
            inHour[hour]=true;
            room[hour]= room;
        }

        LectureGroup(const LectureGroup &other) : students(other.students) {
            for (int i = 0; i < HOURS; ++i) {
                inHour[i] = other.inHour[i];
                rooms[i] = other.rooms[i];
            }
        }
//
//        void addLecture(int hour, int room) {
//            hour--;
//            //TODO- check in hash if the room is available! this is done outside, not here.
//            if (hour < 0 || hour > HOURS || room <= 0)
//                throw InvalidInput();
//            if (inHour[hour])
//                throw Failure();
//            inHour[hour] = true;
//            rooms[hour] = room;
//        }
//
//        void deleteLecture(int hour, int room) {
//            hour--;
//            if (hour < 0 || hour > HOURS || room <= 0)
//                throw InvalidInput();
//            inHour[hour] = false;
//            rooms[hour] = 0;
//
//        }

        LectureGroup operator+(const LectureGroup &other) {
            LectureGroup group(other);
            for (int i = 0; i < HOURS; ++i) {
                if (inHour[i] && other.inHour[i])
                    throw Failure();
                if (inHour[i]) {
                    group.inHour[i] = true;
                    group.rooms[i] = rooms[i];

                } else if (other.inHour[i]) {
                    group.inHour[i] = true;
                    group.rooms[i] = other.rooms[i];
                } else
                    group.inHour[i] = false;
            }
            return group;
        }


    };

    class CourseID {
        friend Schedule2;
        int numStudent;
        int numCourse;
        AVLtree<int, LectureGroup> lectures;
        AVLCounter<int> bestGroups;


    public:
        CourseID(int id) : numStudent(0),
                           numCourse(id), lectures(), bestGroups() {}
        CourseID() : numStudent(0),
                           numCourse(0), lectures(), bestGroups() {}
        CourseID(const CourseID& other) : numStudent(other.numStudent),
                           numCourse(other.numCourse), lectures(other.lectures), bestGroups(other.bestGroups) {}

        ~CourseID() {}

        CourseID &operator+=(CourseID &other) {
            numStudent += other.numStudent;
            return *this;
        }

    };

    class IntArray {
        int *arr;
        int * data;
        friend Schedule2;

    public:
        IntArray(int size) {
            arr = new int[size];
            data = new int[size];
            for (int i = 0; i < size; ++i) {
                arr[i] = 0;
                data[i] = 0;
            }
        }

        int *operator[](int i) {
            return arr + i;
        }

        ~IntArray() {
            delete[] arr;
        }
    };


    HashTable<IntArray> roomsHash;
    UnionFind<CourseID> courses;
    int coursesNum;

public:

    Schedule2(int n) : roomsHash(100), courses(n), coursesNum(n) {}

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
        if (roomsHash.member(roomId))
            throw Failure();
        IntArray arr = roomsHash.getDataByKey(roomId);
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
        IntArray arr = roomsHash.getDataByKey(roomID);
        if (arr[hour - 1])
            throw Failure();
        courseID--;
        *(arr[hour - 1]) = courseID;
        arr.data[hour-1]= groupID;

        CourseID id = courses.Find(courseID - 1);
        id.numStudent+=numStudents;
        if (id.lectures.elementExistsByKey(groupID)){
            LectureGroup exist= id.lectures.getDataByKey(groupID);
            exist.inHour[hour-1]= true;
            exist.rooms[hour-1]= roomID;
        }
        else
            id.lectures.insert(groupID, LectureGroup(numStudents, hour-1, roomID));
        id.bestGroups.insert(numStudents);
    }

    void deleteLecture(int hour, int roomID){
        if (hour<1 || hour>10 || roomID<=0)
            throw InvalidInput();
        if (!roomsHash.member(roomID))
            throw Failure();
        IntArray array= roomsHash.getDataByKey(roomID);
        if (!(*array[hour-1]))
            throw Failure();
        int courseID= (*array[hour-1]);
        (*array[hour-1])= 0;
        CourseID c= courses.Find(courseID);
        int groupID= array.data[hour-1];
        array.data[hour-1]= 0;
        LectureGroup l= c.lectures.getDataByKey(groupID);
        l.inHour[hour-1]= false;
        l.rooms[hour-1]= 0;
        for (int i = 0; i < HOURS; ++i) {
            if (l.inHour[i])
                return;
        }

        c.lectures.remove(groupID);

    }

    void  mergeCourses(int courseID1, int courseID2){
        if (courseID1>coursesNum || courseID2>coursesNum|| courseID1<1 || courseID2<1)
            throw InvalidInput();
        courseID1--;
        courseID2--;
        courses.Union(courseID1, courseID2);
    }



};

#endif //DATASTRUCTUREWET2_SCHEDULE2_H
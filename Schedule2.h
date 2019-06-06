//
// Created by tsofi on 06/06/2019.
//

#ifndef DATASTRUCTUREWET2_SCHEDULE2_H
#define DATASTRUCTUREWET2_SCHEDULE2_H
#define HOURS 10

#include "AVLRankCounter.h"
#include "UnionFind.h"
#include "Wet2Exceptions.cpp"

using namespace Wet2Utils;

class Schedule2 {
    class LectureGroup {
        int groupId;
        bool inHour[HOURS];
        int students;
        int rooms[HOURS];
    public:
        LectureGroup(int id, int s) : groupId(id), students(s) {}

        void addLecture(int hour, int room) {
            hour--;
            //TODO- check in hash if the room is available! this is done outside, not here.
            if (hour < 0 || hour > HOURS || room<=0)
                throw InvalidInput();
            if (inHour[hour])
                throw Failure();
            inHour[hour] = true;
            rooms[hour]=room;
        }

        void deleteLecture(int hour, int room){
            hour--;
            if (hour < 0 || hour > HOURS || room<=0)
                throw InvalidInput();
            inHour[hour]= false;
            rooms[hour]=0;

        }

        bool operator>(LectureGroup& other){
            if(students> other.students)
                return true;
            if (students<other.students)
                return false;
            if(groupId>other.groupId)
                return true;
            if(groupId<other.groupId)
                return false;
            throw AlreadyExist();
        }

        bool operator<(LectureGroup& other){
            return !(this->operator>(other));
        }

    };

    class CourseID {
        int numStudent;
        int numLecture;
        int numCourse;
        AVLRankCounter<LectureGroup> lectures;


    public:
        CourseID(int id) : numStudent(0), numLecture(0), numCourse(id), lectures() {}

        ~CourseID() {}

        CourseID &operator+=(CourseID &other) {
            numStudent += other.numStudent;
            numLecture += other.numLecture;
        }
    };


    UnionFind<CourseID> courses;

};

#endif //DATASTRUCTUREWET2_SCHEDULE2_H

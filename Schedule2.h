//
// Created by tsofi on 06/06/2019.
//

#ifndef DATASTRUCTUREWET2_SCHEDULE2_H
#define DATASTRUCTUREWET2_SCHEDULE2_H
#define HOURS 10

#include "AVLtree.h"
#include "UnionFind.h"
#include "Wet2Exceptions.cpp"

using namespace Wet2Utils;

class Schedule2 {
    class LectureGroup {
        bool inHour[HOURS];
        int students;
        int rooms[HOURS];
    public:
        LectureGroup(int s) : students(s) {}

        LectureGroup(const LectureGroup &other):students(other.students) {
            for (int i = 0; i < HOURS; ++i) {
                inHour[i]= other.inHour[i];
                rooms[i]= other.rooms[i];
            }
        }

        void addLecture(int hour, int room) {
            hour--;
            //TODO- check in hash if the room is available! this is done outside, not here.
            if (hour < 0 || hour > HOURS || room <= 0)
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

        LectureGroup &operator+(const LectureGroup &other) {
            LectureGroup group(students + other.students);
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

                return group;
            }
        }


    };

    class CourseID {
        int numStudent;
        int numLecture;
        int numCourse;
        AVLtree<LectureGroup> lectures;


    public:
        CourseID(int id) : numStudent(0), numLecture(0), numCourse(id), lectures() {}

        ~CourseID() {}

        CourseID &operator+=(CourseID &other) {
            numStudent += other.numStudent;
            numLecture += other.numLecture;
            return *this;
        }
    };


    UnionFind<CourseID> courses;

};

#endif //DATASTRUCTUREWET2_SCHEDULE2_H

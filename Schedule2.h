//
// Created by lucio on 6/6/2019.
//

#ifndef WET2_SCHEDULE2_H
#define WET2_SCHEDULE2_H


#include "AVLRankTree.h"
#include "DynamicHash.h"


class Schedule2{


    class groupID{
        int numStudents;
        int numLectures;
        int courseID;
        AVLRankTree<> students_ranktree;
    };

private:
    DynamicHash<> RoomsHash;
    UnionFind<groupID> course_uf;
    int course_num; // we receive this at initiation
    int m; // set number of hours, will be defined as 10



};


#endif //WET2_SCHEDULE2_H

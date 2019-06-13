#include "library2.h"
#include <assert.h>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#define m 10

using namespace std;
static int CL=0;

class data {

public:


    int groupid;
    int hour;
    int room;
    int students;

    data(int g, int h, int s, int r) {
        groupid = g;
        room = r;
        hour = h;
        students = s;
    }

    friend bool operator==(const data &d1, const data &d2) {

        return (d1.room == d2.room && d1.hour == d2.hour);

    }


};

class test {

public:

    list<int> *mcourses;
    void *DS;
    list<data> *courses; //array of lectures. crouses are numbered 1,2,..,n
    list<int> *occupiedroomsbyhour; //occupied rooms;
    list<int> allrooms;// allrooms// all rooms, orccupied or free/
    int size;

    explicit test(test &t) {

        mcourses = t.mcourses;
        DS = t.DS;
        courses = t.courses;
        occupiedroomsbyhour = t.occupiedroomsbyhour;
        allrooms = t.allrooms;
        size = t.size;

    }

    explicit test(int n) {

        DS = Init(n);
        size = n + 1;
        mcourses = new list<int>[n + 1];
        courses = new list<data>[n + 1];
        occupiedroomsbyhour = new list<int>[m + 1];
        allrooms = *(new list<int>());

        for (int i = 1; i < size; i++) {
            courses[i] = *(new list<data>());
            mcourses[i] = *(new list<int>());;
            mcourses[i].push_back(i);
        }

        for (int i = 1; i < m + 1; i++) {
            occupiedroomsbyhour[i] = *(new list<int>());
        }

    }

    bool checkiflectureexists(int room) {

        for (int i = 1; i < m + 1; i++) {

            if (std::find(occupiedroomsbyhour[i].begin(),
                          occupiedroomsbyhour[i].end(), room) !=
                occupiedroomsbyhour[i].end())
                return true;


        }
        return false;
    }


    test *init(int n) {

        test *newtest = new test(n);
        if (0 >= n) {
            assert(newtest->DS == nullptr);
            return nullptr;
        }

        return newtest;
    }

    void addroom(int room) {

        if (0 >= room) {
            assert(addRoom(DS, room) == INVALID_INPUT);
            return;
        }

        if (std::find(allrooms.begin(), allrooms.end(), room) !=
            allrooms.end()) {
            assert(addRoom(DS, room) == FAILURE);
            return;
        }

        allrooms.push_back(room);

        assert(addRoom(DS, room) == SUCCESS);
    }

    void deleteroom(int room) {

        if (0 >= room) {
            assert(deleteRoom(DS, room) == INVALID_INPUT);
            return;
        }
        if (checkiflectureexists(room)) {
            assert(deleteRoom(DS, room) == FAILURE);
            return;
        }


        if (std::find(allrooms.begin(), allrooms.end(), room) ==
            allrooms.end()) {
            assert(deleteRoom(DS, room) == FAILURE);
            return;
        }

        assert(deleteRoom(DS, room) == SUCCESS);
        allrooms.remove(room);


    }

    int searchbyroomhour(int room, int hour) {

        for (int i = 1; i < size; i++) {

            auto it = courses[i].begin();

            while (it != courses[i].end()) {

                if ((*it).hour == hour && (*it).room == room)
                    return i;

                ++it;

            }

            return -1;

        }


    }

    void addlecture(int courseID, int groupID,
                    int roomID, int hour, int numStudents) {

        if (courseID >= size || groupID < 0 || 0 >= courseID ||
            0 > numStudents ||
            0 >= hour || hour > m || 0 >= roomID) {
            assert(addLecture(DS, courseID, groupID, roomID, hour,
                              numStudents) == INVALID_INPUT);
            return;
        }

        int courseid = getcourseid(courseID);

        auto itt = occupiedroomsbyhour[hour].begin();

        while (itt != occupiedroomsbyhour[hour].end()) {

            if ((*itt) == roomID) {

                assert(addLecture(DS, courseID, groupID, roomID, hour,
                                  numStudents) == FAILURE);
                return;

            }

            ++itt;

        }

        auto it2 = allrooms.begin();

        bool r = false;

        while (it2 != allrooms.end()) {

            if (*it2 == roomID) {
                r = true;
                break;
            }

            ++it2;
        }

        if (!r) {
            assert(addLecture(DS, courseID, groupID, roomID, hour,
                              numStudents) == FAILURE);

            return;
        }

//        bool r =checkiflectureexists(roomID);
//
//        if (r) {
//            assert(addLecture(DS, courseID, groupID, roomID, hour,
//                              numStudents) == FAILURE);
//            return;
//        }

        int c = getcourseid(courseID);

        auto it = courses[c].begin();

        bool u = false;

        while (it != courses[getcourseid(courseID)].end()) {

            if ((*it).groupid == groupID && (*it).hour == hour) {
                u = true;
                break;
            }

            ++it;
        }

        if (u) {
            assert(addLecture(DS, courseID, groupID, roomID, hour,
                              numStudents) == FAILURE);
            return;
        }


        courses[courseid].push_back(
                *(new data(groupID, hour, numStudents, roomID)));
        occupiedroomsbyhour[hour].push_back(roomID);

//        data d(0,7,0,104);
//
//        bool e = std::find(courses[103].begin(), courses[103].end(), d) !=
//                 courses[103].end();

        if(courseID==24)
            CL++;

        assert(addLecture(DS, courseID, groupID, roomID, hour, numStudents) ==
               SUCCESS);

    }

    bool possible(list<data> d1, list<data> d2) {

        auto it1 = d1.begin();
        auto it2 = d2.begin();

        list<double> tmp;

        while (it1 != d1.end()) {

            double key = (*it1).groupid + (double) 1 / (1 + (*it1).hour);
            tmp.push_back(key);
            ++it1;
        }

        while (it2 != d2.end()) {
            double key = (*it2).groupid + (double) 1 / (1 + (*it2).hour);
            tmp.push_back(key);
            ++it2;
        }

        tmp.sort();

        auto tmp1 = tmp.begin();
        auto tmp2 = tmp.begin();
        ++tmp2;

        while (tmp2 != tmp.end()) {

            if (*tmp1 == *tmp2)
                return false;

            ++tmp1;
            ++tmp2;
        }

        return true;

    }

    void deletelecture(int roomid, int hour) {


        data d(0, hour, 0, roomid);

        if (0 >= roomid || 0 >= hour || hour > m) {
            assert(deleteLecture(DS, hour, roomid) == INVALID_INPUT);
            return;
        }

        if (std::find(allrooms.begin(), allrooms.end(), roomid) ==
            allrooms.end()) {
            assert(deleteLecture(DS, hour, roomid) == FAILURE);
            return;
        }

        bool u = false;
        int k = 0;

        for (int i = 1; i < size; i++) {

            if (std::find(courses[i].begin(), courses[i].end(), d) !=
                courses[i].end()) {
                u = true;
                k = i;
                break;
            }
        }


        if (!u) {
            assert(deleteLecture(DS, hour, roomid) == FAILURE);
            return;
        }

        courses[k].remove(d);
        if(k==24 && CL>0)
            CL--;
        occupiedroomsbyhour[hour].remove(roomid);
        if (deleteLecture(DS, hour, roomid) != SUCCESS){
            deleteLecture(DS, hour, roomid);
        }
     //   assert(deleteLecture(DS, hour, roomid) == SUCCESS);

    }

    int sumtopk(list<data> d, int k) {

        int sum = 0;

        list<int> tmp;

        auto it = d.begin();

        while (it != d.end()) {

            tmp.push_back((*it).students);
            ++it;

        }

        tmp.sort();

        int counter = 0;

        int dis = tmp.size() - k;

        auto tmp2 = tmp.begin();

        while (dis > 0) {

            ++tmp2;
            dis--;

        }

        while (tmp2 != tmp.end()) {

            sum += *tmp2;
            ++tmp2;
        }

        return sum;
    }

    int getcourseid(int x) {

        for(int i=1; i<size; i++){

            if(std::find(mcourses[i].begin(),
                         mcourses[i].end(), x) !=
               mcourses[i].end())

                return i;
        }

    }

    void mergecourses(int courseid1, int courseid2) {


//        cout<<"courseid1 ";
//        cout<<"\n";
//        cout<<courseid1;
//        cout<<"\n";
//        cout<<"courseid2 ";
//        cout<<"\n";
//        cout<<courseid2;
//        cout<<"\n";


        if (0 >= courseid1 || 0 >= courseid2 || size <= courseid1 ||
            size <= courseid2) {
            assert(mergeCourses(DS, courseid1, courseid2) == INVALID_INPUT);
            return;
        }
        if (courseid2 == courseid1 ||
            getcourseid(courseid2) == getcourseid(courseid1)) {

            if (mergeCourses(DS, courseid1, courseid2) != FAILURE){
                std::cout << "The problem with mergeCourses is that merge between first courseID1: "
                          << courseid1 << " and second courseID2: " << courseid2 << " Didnt return failure :(" << std::endl;
                std::cout << "BRKPNT here"<< std::endl;
            }
            assert(mergeCourses(DS, courseid1, courseid2) == FAILURE);
            return;
        }

        int r2 = getcourseid(courseid2);
        int r1 = getcourseid(courseid1);

        if (!possible(courses[r1], courses[r2])) {

            assert(mergeCourses(DS, courseid1, courseid2) == FAILURE);
            return;

        }

        // courses[r1].merge(courses[r1],courses[r2]);

        auto it = courses[r2].begin();

        while (it != courses[r2].end()) {

            courses[r1].push_back(*it);
            ++it;

        }

        //r2 becomes r1

        courses[r2] = *(new list<data>()); //may be shit, check later

        auto ptr = mcourses[r2].begin();

        while(ptr!=mcourses[r2].end()){

            mcourses[r1].push_back(*ptr);
            ++ptr;

        }


        mcourses[r2] = *(new list<int>());

        assert(mergeCourses(DS, courseid1, courseid2) == SUCCESS);

    }

    void competition(int courseid1, int courseid2, int lectures) {// <<HELL ON EARTH T_T

        int winner = -1;

        if (courseid1 >= size || courseid2 >= size || 0 >= courseid1 ||
            0 >= courseid2 ||
            0 >= lectures) {

            assert(::competition(DS, courseid1, courseid2, lectures, &winner) ==
                   INVALID_INPUT);
            return;
        }


        int r1 = getcourseid(courseid1);
        int r2 = getcourseid(courseid2);

        size_t size1 = courses[r1].size();
        size_t size2 = courses[r2].size();

        int totalsum1 = 0;
        int totalsum2 = 0;

        auto it1 = courses[r1].begin();
        auto it2 = courses[r2].begin();

//        while(it1!=courses[r1].end()) {
//            totalsum1 += (*it1).students;
//            ++it1;
//        }
//
//        while(it2!=courses[r2].end()) {
//            totalsum2 += (*it2).students;
//            ++it2;
//        }
        if (courseid1 == courseid2 || r1 == r2) {
            if (::competition(DS, courseid1, courseid2, lectures, &winner) !=
                FAILURE){
                std::cout << "The problem with competition is that competition between first courseID1: "
                          << courseid1 << " and courseID: " << courseid2 << " Didnt return fail :(" << std::endl;
                std::cout << "BRKPNT here"<< std::endl;
                ::competition(DS, courseid1, courseid2, lectures, &winner);
            }
            assert(::competition(DS, courseid1, courseid2, lectures, &winner) ==
                   FAILURE);
            return;

        }
        int course1sum = sumtopk(courses[r1], lectures);
        int course2sum = sumtopk(courses[r2], lectures);
        int pos;

        assert(::competition(DS, courseid1, courseid2, lectures, &winner) ==
               SUCCESS);

        if (course1sum > course2sum)
            pos = courseid1;

        if (course2sum > course1sum)
            pos = courseid2;

        if (course1sum == course2sum && courseid1 > courseid2)
            pos = courseid1;

        if (course1sum == course2sum && courseid1 < courseid2)
            pos = courseid2;
//
//        cout << winner;
//        cout << "\n";
//        cout << pos;
//        cout << "\n";

        if (pos != winner){
            std::cout << "The problem with competition is that pos isn't equal to winner! Pos is: "
                      << pos << " and winner is : " << winner << std::endl;
            std::cout << "BRKPNT here"<< std::endl;
            ::competition(DS, courseid1, courseid2, lectures, &winner);
        }
        assert(pos == winner);

    }

    void getaveragestudentsincourse(int roomid, int hour) {

        float g = -1;

        if (0 >= roomid || 0 >= hour || hour > m) {
            assert(getAverageStudentsInCourse(DS, hour, roomid, &g) ==
                   INVALID_INPUT);
            return;
        }
        data d(0, hour, 0, roomid);


        if (std::find(allrooms.begin(), allrooms.end(), roomid) ==
            allrooms.end())
            assert(getAverageStudentsInCourse(DS, hour, roomid, &g) == FAILURE);

        bool u = false;

//        for(int i=1; i<m+1; i++) {
//           if(std::find(occupiedroomsbyhour[i].begin(),
//                      occupiedroomsbyhour[i].end(), roomid) !=  <<<---useless
//            occupiedroomsbyhour[i].end())
//               u = true;
//        }

        //  if(!u)
        //    assert(getAverageStudentsInCourse(DS,hour,roomid,&g)==FAILURE);

        //  auto it = courses[1].begin();
        int courseid = -1;

        for (int i = 1; i < size; i++) {
            auto it = courses[i].begin();
            while (it != courses[i].end()) {

                if ((*it).hour == hour && (*it).room == roomid)
                    courseid = i;

                ++it;

            }

            //  it = courses[i].begin();

        }

        if (courseid == -1) {
            assert(getAverageStudentsInCourse(DS, hour, roomid, &g) == FAILURE);
            return;
        }

        float sum = 0;

        int rcourseid = getcourseid(courseid);

        auto it = courses[rcourseid].begin();

        while (it != courses[rcourseid].end()) {

            sum += (*it).students;
            ++it;
        }

        size_t tmp = courses[rcourseid].size();

        assert(getAverageStudentsInCourse(DS, hour, roomid, &g) == SUCCESS);



//        if(tmp==61)
//            cout<<CL;

        std::cout<<"g= "<<g<<" his= "<<(sum / (float) courses[courseid].size())<<std::endl;
        assert(g < sum / (float) courses[courseid].size()+0.2 && g >sum / (float) courses[courseid].size()-0.2 );


    }
};


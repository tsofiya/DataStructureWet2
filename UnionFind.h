//
// Created by tsofi on 05/06/2019.
//

#ifndef DATASTRUCTUREWET2_UNIONFIND_H
#define DATASTRUCTUREWET2_UNIONFIND_H

template <class T>
class UnionFind{
private:
    int * groupsIDs;
    T * groups;
    int size

public:
    UnionFind(int s):size(s){
        groupsIDs= new [size];
        groups= new [size];

        for (int i = 0; i < size; ++i) {
            groupsIDs[i]= i;
            groups[i]= T(i);
        }

        T& find(int find){

        }
    }

    ~UnionFind(){
        delete[](groups);
        delete[](groupsIDs);
    }

    //what should I return here? correct this if necessary
    T& Find(int id){
        int grp= recFind(id);
        return groups[grp];
    }

    //Decision: when we implement T as ids and so, we will implement +=.
    void Union(int id1, int id2){
        groupsIDs[id1]= id2;
        groups[id2]+=groups[id1];
    }

private:
    //check for correctness
    int recFind(int id){
        if (groupsIDs[id]==id)
            return id;
        int grp= recFind(groupsIDs[id]);
        groupsIDs[id]= grp;
        return grp;
    }
};

#endif //DATASTRUCTUREWET2_UNIONFIND_H

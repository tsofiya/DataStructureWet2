#include <iostream>
#include "AVLRankCounter.h"

int main() {
    std::cout << "Creating rank tree" << std::endl;
    AVLRankCounter<int> tree;
    tree.insert(8);
    tree.insert(13);
    tree.insert(7);
    tree.insert(6);
    tree.insert(3);
    tree.insert(4);
    tree.insert(25);
    tree.insert(25);
    tree.insert(3);
    tree.insert(17);
    tree.insert(16);
    tree.insert(21);
    tree.insert(21);
    tree.insert(18);
    tree.insert(9);
    tree.insert(11);
    tree.inOrderPrint();

    tree.remove(3);
    tree.remove(21);
    tree.remove(9);
    tree.inOrderPrint();

    return 0;
}
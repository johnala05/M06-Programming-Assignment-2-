#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>

class BTreeNode {
public:
    bool leaf;
    int t; // minimum degree
    std::vector<int> keys;
    std::vector<BTreeNode*> children;

    BTreeNode(int t, bool leaf);
    void traverse();
    BTreeNode* search(int k);

    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
};

class BTree {
private:
    BTreeNode* root;
    int t; // minimum degree

public:
    BTree(int t);
    void traverse();
    BTreeNode* search(int k);
    void insert(int k);
};

#endif

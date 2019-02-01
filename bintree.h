//
// Created by Jarod on 1/28/2019.
//

#ifndef ASSIGNMENT2_BINTREE_H
#define ASSIGNMENT2_BINTREE_H

#include "nodedata.h"
#include <iostream>
class BinTree
{
    friend std::ostream& operator<<(std::ostream &outStream, const BinTree &b);

public:
    BinTree();
    BinTree(BinTree &b);
    ~BinTree();

    void bstreeToArray(NodeData* arr[]);
    void arrayToBSTree(NodeData* arr[]);

    bool isEmpty() const;
    void makeEmpty();
    bool retrieve(const NodeData &target, NodeData* &pTarget);
    bool insert(NodeData* item);
    int getHeight(const NodeData &n) const;
    void displaySideways() const;

    // Overload operators
    BinTree& operator=(const BinTree &b);
    bool operator==(const BinTree &b) const;
    bool operator!=(const BinTree &b) const;

private:
    struct Node
    {
        NodeData* data;
        Node* left;
        Node* right;

    };
    Node* root;

    // Utility functions
    void inorderHelper(Node* current, int &index, NodeData* arr[]) const;
    void arrayToBSTHelper(Node* current, int low, int high, NodeData* arr[]);
    void copyHelper(Node* lhs, Node *rhs);
    void deleteHelper(Node* current);
    Node* retrieveHelper(Node* current, const NodeData &target) const;
    int heightHelper(const Node* current, const NodeData &target, int height) const;
    void insertHelper(Node* current, NodeData* item);
    bool equalityHelper(const Node* current, const Node* other) const;
    void sideways(Node* current, int level) const;
    void coutHelper(std::ostream &outStream, const Node* current, int level) const;
    const int ARRAYSIZE = 100;
};
#endif //ASSIGNMENT2_BINTREE_H

//
// Created by Jarod on 1/28/2019.
//

#ifndef ASSIGNMENT2_BINTREE_H
#define ASSIGNMENT2_BINTREE_H

#include "nodedata.h"
class BinTree
{
    friend std::ostream operator<<(std::ostream &outStream, const BinTree &b);
    friend std::istream operator>>(std::istream &inStream, const BinTree &b);

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
    void inorderHelper() const;
    void copyHelper(Node* lhs, Node *rhs);
    void deleteHelper(Node* current);
    Node* retrieveHelper(Node* current, const NodeData &target) const;
    void insertHelper(Node* current, NodeData* item);
    void sideways(Node* current, int level) const;
};
#endif //ASSIGNMENT2_BINTREE_H

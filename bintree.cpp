#include "bintree.h"

using namespace std;

std::ostream operator<<(std::ostream &outStream, const BinTree &b)
{
    return std::ostream(nullptr);
}

std::istream operator>>(std::istream &inStream, const BinTree &b)
{
    return std::istream(nullptr);
}

/*
 * Default constructor creates an empty tree
 */
BinTree::BinTree()
{
    root = nullptr;
}

/*
 * Creates a deep copy of another binary tree and
 * all its elements. Uses pre-order traversal
 */
BinTree::BinTree(BinTree &b)
{
    copyHelper(root, b.root);
}

/*
 * Helper function for the copy constructor.
 * Traverses a tree inorder and creates a new node.
 */
void BinTree::copyHelper(BinTree::Node *lhs, BinTree::Node *rhs)
{   // Other tree is empty
    if(lhs == nullptr && rhs == nullptr)
    {
        return;
    }
    // Other tree is not empty
    if(root == nullptr && rhs != nullptr)
    {
        root = new Node;
        root->data = new NodeData(*rhs->data);
    }
    // Copy left then follow if not a leaf
    if(rhs->left != nullptr)
    {
        lhs->left = new Node;
        lhs->left->data = new NodeData(*rhs->left->data);
        copyHelper(lhs->left, rhs->left);
    }
    else // Left is null
    {
        lhs->left = nullptr;
    }
    // Copy right then follow if not a leaf
    if(rhs->right != nullptr)
    {
        lhs->right = new Node;
        lhs->right->data = new NodeData(*rhs->right->data);
        copyHelper(lhs->right, rhs->right);
    }
    else // Right is null
    {
        lhs->right = nullptr;
    }
}

/*
 * Destructor
 */
BinTree::~BinTree()
{
    makeEmpty();
}

void BinTree::bstreeToArray(NodeData **arr)
{

}

void BinTree::arrayToBSTree(NodeData **arr)
{

}

/*
 * Returns whether the tree is empty.
 * An empty tree is one where its root is null.
 */
bool BinTree::isEmpty() const
{
    return root == nullptr;
}

/*
 * Empties the BST by removing all nodes from it.
 * The NodeData in each Node is also deleted.
 */
void BinTree::makeEmpty()
{
    deleteHelper(root);
    // Manually set root to nullptr
    root = nullptr;
}

/*
 * Helper function for makeEmpty() used to iterate
 * through the BST in post-order. Deletes all nodes
 * and their
 */
void BinTree::deleteHelper(BinTree::Node *current)
{
    // Left
    if(current->left != nullptr)
    {
        deleteHelper(current->left);
    }
    // Right
    if(current->right != nullptr)
    {
        deleteHelper(current->right);
    }
    delete current->data;
    delete current;
}

/*
 * Retrieves the NodeData pointer of an object in the tree
 * and reports whether it was found.
 * The NodeData* &p parameter may initially be garbage, then
 * if found, will point to the actual object in the tree.
 * If not found, it will not be changed.
 */
bool BinTree::retrieve(const NodeData &target, NodeData *&pTarget)
{
    // pTarget will be assigned depending on whether the target
    // is found in the tree. If not found, it will be null. If
    // found, the target the pTarget should have the same data
    Node* temp = retrieveHelper(root, target);
    if(temp == nullptr){
        return false;
    }
    pTarget = temp->data;
    return true;
}

/*
 * Helper function for retrieve.
 * Returns the Node with the target's data if found.
 * Otherwise returns a nullptr.
 */
BinTree::Node *BinTree::retrieveHelper(BinTree::Node *current, const NodeData &target) const
{
    // Empty tree or object not found (hit a leaf)
    if(current == nullptr)
    {
        return nullptr;
    }
    // Node data found!
    else if(target == *current->data)
    {
        return current;
    }
    // Node data is less than current data. Go left
    else if(target < *current->data)
    {
        return retrieveHelper(current->left, target);
    }
    // Node data is greater than current data. Go right
    else if(target > *current->data)
    {
        return retrieveHelper(current->right, target);
    }
}

/*
 * Inserts an item into the correct spot in the BinarySearchTree.
 * Creates a new tree if empty.
 */
bool BinTree::insert(NodeData *item)
{
    insertHelper(root, item);
    return true;
}

/*
 *
 */
void BinTree::insertHelper(BinTree::Node *current, NodeData *item)
{
    // Empty tree or leaf
    if (current == nullptr)
    {
        current = new Node;
        current->data = item;
        current->left = nullptr;
        current->right = nullptr;
    }
        // Dereference to refer to the string values
    else if (*item < *current->data)
    {
        insertHelper(current->left, item);
    }
    else
    {
        insertHelper(current->right, item);
    }
}

/*
 * Returns the height of the binary search tree from a
 * given Node. The height of a node at a leaf is 1.
 * Height of a value not found is 0.
 */
int BinTree::getHeight(const NodeData &n) const
{
    return 0;
}

/*
 * Displays a binary tree as though you are viewing it from the side;
 * hard coded displaying to standard output.
 * Preconditions: NONE
 * Postconditions: BinTree remains unchanged.
 */
void BinTree::displaySideways() const
{
    sideways(root, 0);
}

BinTree &BinTree::operator=(const BinTree &b)
{
    return <#initializer#>;
}

bool BinTree::operator==(const BinTree &b) const
{
    return false;
}

bool BinTree::operator!=(const BinTree &b) const
{
    return false;
}

void BinTree::inorderHelper() const
{

}

/*
 * Helper method for displaySideways
 * Preconditions: NONE
 * Postconditions: BinTree remains unchanged.
 */
void BinTree::sideways(BinTree::Node *current, int level) const
{
    if (current != NULL)
    {
        level++;
        sideways(current->right, level);
        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            cout << "    ";
        }
        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}

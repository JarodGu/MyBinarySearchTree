#include "bintree.h"

using namespace std;

/*
 * Overloads the cout operator using the same method
 * as displaySideways.
 */
std::ostream& operator<<(std::ostream &outStream, const BinTree &b)
{
    b.coutHelper(outStream, b.root, 0);
    return outStream;
}

void BinTree::coutHelper(std::ostream &outStream, const BinTree::Node *current, int level) const
{
    if (current != nullptr)
    {
        level++;
        sideways(current->right, level);
        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            outStream << "    ";
        }
        outStream << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
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

void BinTree::bstreeToArray(NodeData *arr[])
{
    int index = 0;
    inorderHelper(root, index, arr);
    makeEmpty();
}

/*
 * Helper function for bstreeToArray used to add items in the
 * tree to a NodeData array using inorder traversal.
 */
void BinTree::inorderHelper(Node* current, int &index, NodeData *arr[]) const
{
    if(current != nullptr)
    {
        // Left
        inorderHelper(current->left, index, arr);
        // Current
        arr[index] = new NodeData(*current->data);
        index++;
        // Right
        inorderHelper(current->right, index, arr);
    }
}

/*
 * Populates a binary search tree with elements from a sorted array.
 * Resulting tree is balanced.
 * Precondition: NodeData* array is sorted and calling tree is empty
 * Postcondition: NodeData* array is filled with nullptr's
 * NOTE, how can I tell the highest element in the array?
 * ANSWER: Since I'm not inserting nullptr's with bstreeToArray,
 *         the size will be the number of non-null values.
 *
 */
void BinTree::arrayToBSTree(NodeData *arr[])
{
    // Get size
    int size = 0;
    while(arr[size] != nullptr)
    {
        size++;
    }
    arrayToBSTHelper(root, 0, size, arr);
}

/*
 * Helper function for arrayToBSTree used to do balanced inserts.
 */
void BinTree::arrayToBSTHelper(BinTree::Node *current, int low, int high, NodeData *arr[])
{
    // Base case
    if( low > high)
    {
        return;
    }
    else
    {
        int mid = (low + high)/2;
        insert(arr[mid]);
        arr[mid] = nullptr;
        arrayToBSTHelper(current->left, low, mid-1, arr);
        arrayToBSTHelper(current->right, mid+1, high, arr);
    }
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
 * given NodeData. The height of a node at a leaf is 1.
 * Height of a value not found is 0.
 */
int BinTree::getHeight(const NodeData &target) const
{
    return heightHelper(root, target, 1);
}

int BinTree::heightHelper(const BinTree::Node *current, const NodeData &target, int height) const
{

    if(current == nullptr)
    {
        return 0;
    }
        // Node data found!
    if(target == *current->data)
    {
        return height;
    }
        // Node data is less than current data. Go left
    else if(target < *current->data)
    {
        return heightHelper(current->left, target, height+1);
    }
        // Node data is greater than current data. Go right
    else if(target > *current->data)
    {
        return heightHelper(current->right, target, height+1);
    }
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


/*
 * Helper method for displaySideways
 * Preconditions: NONE
 * Postconditions: BinTree remains unchanged.
 */
void BinTree::sideways(BinTree::Node *current, int level) const
{
    if (current != nullptr)
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

/*
 * Assigns the values of one tree to another by making
 * a deep copy. Values in the original tree are deleted
 * and replaced with the new one.
 */
BinTree &BinTree::operator=(const BinTree &b)
{
    //Self assignment
    if(this == &b){
        return *this;
    }
    // Empty the lhs tree
    makeEmpty();
    // Copy values in rhs to lhs
    copyHelper(root, b.root);
    return *this;
}

/*
 * Returns true of two BST's are the same.
 * Each Node must be in the same place with the same NodeData.
 */
bool BinTree::operator==(const BinTree &b) const
{
    return equalityHelper(root, b.root);
}

bool BinTree::operator!=(const BinTree &b) const
{
    return !equalityHelper(root, b.root);
}

/*
 * Helper function for the equality operator overload.
 */
bool BinTree::equalityHelper(const BinTree::Node *current, const BinTree::Node *other) const
{
    if(current == nullptr && other == nullptr)
    {
        return true;
    }
    if(current != nullptr && other != nullptr)
    {
        return
        (
                *current->data == *other->data
                && equalityHelper(current->left, other->left)
                && equalityHelper(current->right, other->right)
        );
    }
    // One nullptr, one not
    return false;
}


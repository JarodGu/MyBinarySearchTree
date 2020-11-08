# Binary Search Tree
My binary search tree implementation with accompanying functions.

## Supported Functions
| Function | Description |
| --- | --- |
| void ```bstreeToArray(NodeData* arr[]);``` | Populates an array from a BST using inorder traversal. Resulting array is sorted and leaves the tree empty.|
| void ```arrayToBSTree(NodeData* arr[]);``` | Populates a binary search tree with elements from a sorted array. Resulting tree is balanced. |
| bool ```isEmpty() const;``` | Returns whether the tree is empty. An empty tree is one where its root is null. |
| void ```makeEmpty();``` | Empties the BST by removing all nodes from it. The NodeData in each Node is also deleted. |
| bool ```retrieve(const NodeData &target, NodeData* &pTarget);``` | Helper function for makeEmpty() used to iterate through the BST in post-order. Deletes all nodes and their data. |
| bool ```insert(NodeData* item);``` | Inserts an item into the correct spot in the BinarySearchTree. Creates a new tree if empty. Returns false if inserting an existing value, otherwise true. |
| int ```getHeight(const NodeData &n) const;``` | Returns the height of an element based on its data. The height of a node at a leaf is 1. Height of a value not found is 0. Height of the root is 1 + the number of connections to the lowest leaf. |
| void ```displaySideways() const;``` | Displays a binary tree as though you are viewing it from the side. Hard coded displaying to standard output. |

## Overload Operators
| Function | Description|
| --- | --- |
| BinTree& ```operator=(const BinTree &b);``` | Assigns the values of one tree to another by making a deep copy. Values in the original tree are deleted and replaced with the new one. |
| bool ```operator==(const BinTree &b) const;``` | Returns true of two BST's are the same. Each Node must be in the same place with the same NodeData. |
| bool ```operator!=(const BinTree &b) const;``` | Returns true of two BST's are not equal. |

/* Use it as the node in the BST MyMap.
 * It does not really need to be templated here, since for the tree, it just contains a MyPair,
 * but you can re-use this for other purposes with it typed, for example, a set.
 * Do not edit this file.
 */

#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
struct TreeNode
{
    T data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(const T &x, TreeNode *lc, TreeNode *rc): data(x), left(lc), right(rc) {}
};

#endif


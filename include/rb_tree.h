// include/rb_tree.h
#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdlib.h>

// == Red-Black Tree Data Structures ==

/**
 * @enum Color
 * @brief Possible colors for nodes in a Red-Black Tree.
 */
typedef enum { RED, BLACK } Color;

/**
 * @struct RBNode
 * @brief A single node in the Red-Black Tree.
 *
 * Each node holds an integer key, its color, and pointers to its
 * left child, right child, and parent.  A special sentinel node (nil)
 * represents all leaves.
 */
typedef struct RBNode {
    int key;               // The key stored in this node.
    Color color;           // RED or BLACK.
    struct RBNode *left;   // Left child (or nil).
    struct RBNode *right;  // Right child (or nil).
    struct RBNode *parent; // Parent (or nil for root).
} RBNode;

/**
 * @struct RBTree
 * @brief The Red-Black Tree container.
 *
 * Holds a pointer to the root node and to the shared sentinel (nil).
 */
typedef struct {
    RBNode *root; // Root of the tree (or nil if empty).
    RBNode *nil;  // Sentinel node, used in place of NULL.
} RBTree;

// == Red-Black Tree methods ==

/**
 * @brief Allocate and initialize an empty Red-Black Tree.
 *
 * Initializes both the RBTree struct and its nil sentinel node:
 *  1) Allocates RBTree and RBNode (nil).
 *  2) Sets nil.color = BLACK, nil.{left,right,parent} = nil.
 *  3) Sets tree->root = nil.
 *
 * @return Pointer to the new RBTree on success, NULL on failure.
 */
RBTree *rb_tree_create(void);

/**
 * @brief Destroy a Red-Black Tree and free its memory.
 *
 * @param t  Pointer to the RBTree to destroy.
 *
 * @note This currently only frees the sentinel and tree struct.
 *       You must traverse and free all data nodes before calling
 *       this (TODO in future).
 */
void rb_tree_destroy(RBTree *t);

/**
 * @brief Perform a left rotation around node x.
 *
 * Transforms this configuration:
 *         parent
 *           |
 *           x
 *          / \
 *         A   y
 *            / \
 *           B   C
 *
 * Into:
 *         parent
 *           |
 *           y
 *          / \
 *         x   C
 *        / \
 *       A   B
 *
 * @param t  The tree on which to perform the rotation.
 * @param x  The pivot node (must not be nil).
 */
void rb_tree_left_rotate(RBTree *t, RBNode *x);

/**
 * @brief Perform a right rotation around node y.
 *
 * Inverse of left_rotate: pivots around y.left.
 *
 * @param t  The tree on which to perform the rotation.
 * @param y  The pivot node (must not be nil).
 */
void rb_tree_right_rotate(RBTree *t, RBNode *y);

#endif // RB_TREE_H

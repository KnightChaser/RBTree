// include/rb_tree.h
#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdio.h>
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

/**
 * @brief Insert a key into the Red-Black Tree.
 *
 * Performs a standard BST insert of a new red node,
 * then calls rb_tree_insert_fixup to restore R-B properties.
 * (which is defined as a static void function)
 *
 * @param t    Pointer to the RBTree.
 * @param key  The integer key to insert.
 */
void rb_tree_insert(RBTree *t, int key);

/**
 * @brief Delete a key from the Red-Black Tree.
 *
 * Removes a node with the given key from the tree.
 * then calls rb_tree_delete_fixup to restore R-B properties.
 * (which is defined as a static void function)
 *
 * @param t   Pointer to the RBTree.
 * @param key The integer key to delete.
 */
void rb_tree_delete(RBTree *t, int key);

/**
 * @brief Traverse the tree in-order and return the node with the given key.
 *
 * @param t  The Red-Black Tree to traverse.
 * @param n  The current node to start from (usually t->root).
 *
 * @return Pointer to the node with the key, or t->nil if not found.
 */
RBNode *rb_tree_search(RBTree *t, int key);

/**
 * @brief Print a node’s key and color to stdout.
 *
 * Prints “nil” if the node is the sentinel.
 *
 * @param t  The Red-Black Tree (for its nil sentinel).
 * @param n  The node to print.
 */
void rb_tree_print_node(RBTree *t, RBNode *n);

#endif // RB_TREE_H

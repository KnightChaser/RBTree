// include/auxiliary.h
#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "rb_tree.h"

/**
 * @brief In-order traversal of the tree.
 *
 * Visits left subtree, prints the node via
 * rb_tree_print_node(), then visits right subtree.
 *
 * @param t  The Red-Black Tree.
 * @param n  The current node to traverse.
 */
void inorder_traverse(RBTree *t, RBNode *n);

/**
 * @brief Prints the node's key and color on the terminal, beautifully.
 *
 * @param t  The Red-Black Tree.
 */
void rb_tree_visualize(RBTree *t);

#endif // AUXILIARY_H

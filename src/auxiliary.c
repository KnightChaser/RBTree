// src/auxiliary.c
#include "../include/auxiliary.h"

/**
 * @brief In-order traversal of the tree.
 *
 * Visits left subtree, prints the node via
 * rb_tree_print_node(), then visits right subtree.
 *
 * @param t  The Red-Black Tree.
 * @param n  The current node to traverse.
 */
void inorder_traverse(RBTree *t, RBNode *n) {
    if (n == t->nil) {
        return;
    }
    inorder_traverse(t, n->left);
    rb_tree_print_node(t, n);
    printf(" ");
    inorder_traverse(t, n->right);
}

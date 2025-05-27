// src/auxiliary.c
#include "../include/auxiliary.h"

// ANSI escape codes
#define ANSI_RED "\x1b[31m"
#define ANSI_WHITE "\x1b[37m"
#define ANSI_RESET "\x1b[0m"

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

/**
 * @brief Recursively print subtree sideways with colors.
 *  - Prints right subtree first (so it shows “above”).
 *  - Indents by depth*4 spaces.
 *  - Colors RED nodes red, BLACK nodes white.
 */
static void _print_subtree(RBTree *t, RBNode *n, int depth) {
    if (n == t->nil) {
        return;
    }
    _print_subtree(t, n->right, depth + 1);

    // indentation
    for (int i = 0; i < depth; i++)
        fputs("    ", stdout);

    // color + label
    const char *col = (n->color == RED) ? ANSI_RED : ANSI_WHITE;
    printf("%s%d(%c)%s\n", col, n->key, n->color == RED ? 'R' : 'B',
           ANSI_RESET);

    _print_subtree(t, n->left, depth + 1);
}

/**
 * @brief Public entry: print the whole tree.
 */
void rb_tree_visualize(RBTree *t) { _print_subtree(t, t->root, 0); }

// src/rb_tree.c
#include "../include/rb_tree.h"

RBTree *rb_tree_create(void) {
    RBTree *t = calloc(1, sizeof(RBTree));
    if (!t) {
        // Memory allocation failed for the Red-Black Tree structure
        return NULL;
    }

    t->nil = calloc(1, sizeof(RBNode));
    if (!t->nil) {
        // Memory allocation failed for sentinel node
        free(t);
        return NULL;
    }

    t->nil->color = BLACK; // Sentinel node is always black
    t->nil->left = t->nil;
    t->nil->right = t->nil;
    t->nil->parent = t->nil; // Sentinel node's parent points to itself
    t->root = t->nil;        // Initially, the root is the sentinel node

    return t;
}

void rb_tree_destroy(RBTree *t) {
    // TODO: walk & free all nodes in the tree
    free(t->nil); // Free the sentinel node
    free(t);      // Free the Red-Black Tree structure
}

void rb_tree_left_rotate(RBTree *t, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != t->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == t->nil) {
        t->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rb_tree_right_rotate(RBTree *t, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != t->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == t->nil) {
        t->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

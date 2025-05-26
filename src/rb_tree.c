// src/rb_tree.c
#include "../include/rb_tree.h"

/**
 * @brief Allocate and initialize an empty Red-Black Tree.
 */
RBTree *rb_tree_create(void) {
    // 1) Allocate the tree structure
    RBTree *t = calloc(1, sizeof(RBTree));
    if (!t) {
        return NULL;
    }

    // 2) Create the nil sentinel node
    t->nil = calloc(1, sizeof(RBNode));
    if (!t->nil) {
        free(t);
        return NULL;
    }

    // 3) Initialize sentinel: always black, points to itself
    t->nil->color = BLACK;
    t->nil->left = t->nil;
    t->nil->right = t->nil;
    t->nil->parent = t->nil;

    // 4) Empty tree: root = nil
    t->root = t->nil;
    return t;
}

/**
 * @brief Destroy a Red-Black Tree and free its memory.
 */
void rb_tree_destroy(RBTree *t) {
    if (!t) {
        return;
    }

    // TODO: traverse from root and free every non-nil node
    free(t->nil);
    free(t);
}

/**
 * @brief Left-rotate the subtree rooted at x.
 *
 * @param t  The Red-Black Tree.
 * @param x  Pivot node where rotation is applied.
 */
void rb_tree_left_rotate(RBTree *t, RBNode *x) {
    RBNode *y = x->right;    // 1) Set y
    x->right = y->left;      // 2) Turn y's left subtree into x's right
    if (y->left != t->nil) { // 3) Update parent pointer for that subtree
        y->left->parent = x;
    }

    // 4) Link y to x's former parent
    y->parent = x->parent;

    if (x->parent == t->nil) {
        // 5a) x was root
        t->root = y;
    } else if (x == x->parent->left) {
        // 5b) x was left child
        x->parent->left = y;
    } else {
        // 5c) x was right child
        x->parent->right = y;
    }

    y->left = x;   // 6) Put x on y's left
    x->parent = y; // 7) Update x's parent
}

/**
 * @brief Right-rotate the subtree rooted at y.
 *        It is the mirror operation of left-rotation.
 *
 * @param t  The Red-Black Tree.
 * @param y  Pivot node where rotation is applied.
 */
void rb_tree_right_rotate(RBTree *t, RBNode *y) {
    RBNode *x = y->left;      // 1) Set x
    y->left = x->right;       // 2) Turn x's right subtree into y's left
    if (x->right != t->nil) { // 3) Update parent pointer for that subtree
        x->right->parent = y;
    }

    // 4) Link x to y's former parent
    x->parent = y->parent;
    if (y->parent == t->nil) {
        // 5a) y was root
        t->root = x;
    } else if (y == y->parent->right) {
        // 5b) y was right child
        y->parent->right = x;
    } else {
        // 5c) y was left child
        y->parent->left = x;
    }

    x->right = y;  // 6) Put y on x's right
    y->parent = x; // 7) Update y's parent
}

// include/rb_tree.h
#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdlib.h>

// == Red-Black Tree structure Implementation ==
// Color of the nodes in the Red-Black Tree
typedef enum { RED, BLACK } Color;

// Structure for a node in the Red-Black Tree
typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;

// Structure for the Red-Black Tree itself
typedef struct RBTree {
    RBNode *root;
    RBNode *nil; // sentinel node
} RBTree;

// == RB Tree functions ==
// Creates a new Red-Black Tree
RBTree *rb_tree_create(void);
// Destroys the Red-Black Tree and frees memory
void rb_tree_destroy(RBTree *t);
// Performs a left rotation on the Red-Black Tree
void rb_tree_left_rotate(RBTree *t, RBNode *x);
// Performs a right rotation on the Red-Black Tree
void rb_tree_right_rotate(RBTree *t, RBNode *y);

#endif // RB_TREE_H

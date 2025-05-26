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

static void rb_tree_insert_fixup(RBTree *t, RBNode *z);

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

/**
 * @brief Insert a new node into the Red-Black Tree.
 *         This function doesn't implement the fixup logic,
 *         which is defined at rb_tree_insert_fixup().
 *
 * @param t    The Red-Black Tree.
 * @param key  The key to insert.
 */
void rb_tree_insert(RBTree *t, int key) {
    // 1) Allocate and initialize the new node z
    RBNode *z = calloc(1, sizeof(RBNode));
    if (!z) {
        return; // Handle allocation failure
    }
    z->key = key;
    z->color = RED; // New nodes are always red initially
    z->left = t->nil;
    z->right = t->nil;
    z->parent = t->nil; // Parent is nil until linked

    // 2) Standard binary search tree insertion: find part y for z
    RBNode *y = t->nil;
    RBNode *x = t->root;
    while (x != t->nil) {
        y = x;
        if (z->key < x->key) {
            // If z's key is less, go left
            x = x->left;
        } else {
            // If z's key is greater or equal, go right
            x = x->right;
        }
    }

    // 3) Link z into the tree
    z->parent = y;
    if (y == t->nil) {
        // tree was empty
        t->root = z;
    } else if (z->key < y->key) {
        // z is a left child
        y->left = z;
    } else {
        // z is a right child
        y->right = z;
    }

    // 4) Call fix up and red-black tree property violation
    rb_tree_insert_fixup(t, z);
}

/**
 * @brief Fix up the Red-Black Tree after insertion.
 *        This function is called after rb_tree_insert().
 *
 * @param t  The Red-Black Tree.
 * @param z  The newly inserted node that may violate properties.
 */
static void rb_tree_insert_fixup(RBTree *t, RBNode *z) {
    RBNode *y;
    // Continue until z is root or parent is black.
    // If the parent is black, it means no violation because
    // the red-black properties are maintained.
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right; // uncle (right)
            if (y->color == RED) {
                // Case 1: Uncle is red -> recolor
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // jump to grandparent node
            } else {
                if (z == z->parent->right) {
                    // Case 2: z is right child -> left rotate
                    // to transform this case into Case 3
                    z = z->parent;
                    rb_tree_left_rotate(t, z);
                }
                // Case 3: z is left child -> right rotate
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_tree_right_rotate(t, z->parent->parent);
            }
        } else {
            // Mirror case: z's parent is right child
            y = z->parent->parent->left; // uncle (left)
            if (y->color == RED) {
                // Case 1': Uncle is red -> recolor
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // jump to grandparent node
            } else {
                if (z == z->parent->left) {
                    // Case 2'
                    z = z->parent;
                    rb_tree_right_rotate(t, z);
                }
                // Case 3'
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_tree_left_rotate(t, z->parent->parent);
            }
        }
    }

    // Ensure root is always black (Don't forget this! >_<)
    t->root->color = BLACK;
}

/**
 * @brief Print a node(RBNode) in the Red-Black Tree.
 *        Used for debugging purposes.
 *
 * @param t  The Red-Black Tree.
 * @param n  The node to print.
 */
void rb_tree_print_node(RBTree *t, RBNode *n) {
    if (n == t->nil) {
        printf("nil");
    } else {
        printf("%d(%s)", n->key, n->color == RED ? "R" : "B");
    }
}

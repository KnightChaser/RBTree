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
 * @brief Recursively free all nodes in the subtree rooted at n.
 *
 * @param t  The Red-Black Tree (for its nil sentinel).
 * @param n  Current subtree root (skip if nil).
 */
static void rb_tree_free_subtree(RBTree *t, RBNode *n) {
    if (n == t->nil) {
        return;
    }

    rb_tree_free_subtree(t, n->left);
    rb_tree_free_subtree(t, n->right);
    free(n);
}

/**
 * @brief Destroy a Red-Black Tree and free its memory.
 *
 * 1) Recursively free all real nodes (post-order).
 * 2) Free the nil sentinel.
 * 3) Free the tree struct.
 *
 * @param t  Pointer to the RBTree to destroy.
 */
void rb_tree_destroy(RBTree *t) {
    if (!t) {
        return;
    }

    rb_tree_free_subtree(t, t->root);
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
 * @brief Transplant one subtree with another.
 *        Used during deletion to replace a node with its child.
 *
 * @param t  The Red-Black Tree.
 * @param u  The node to be replaced.
 * @param v  The node to replace with.
 */
static void rb_tree_transplant(RBTree *t, RBNode *u, RBNode *v) {
    if (u->parent == t->nil) {
        // u is root
        t->root = v;
    } else if (u == u->parent->left) {
        // u is left child
        u->parent->left = v;
    } else {
        // u is right child
        u->parent->right = v;
    }
    v->parent = u->parent;
}

/**
 * @brief Return the node with the minimum key in the subtree rooted at x.
 *
 * @param t  The Red-Black Tree.
 * @param x  The node to start searching from.
 */
static RBNode *rb_tree_minimum(RBTree *t, RBNode *x) {
    while (x->left != t->nil) {
        // Go left until we reach the leftmost node
        x = x->left;
    }
    return x;
}

static void rb_tree_delete_fixup(RBTree *T, RBNode *x);

/**
 * @brief Delete a node with the given key from the Red-Black Tree.
 *        This function implements the deletion logic and calls
 *        rb_tree_delete_fixup() to maintain properties.
 *
 *        1) Find the node z to delete.
 *        2) Prepare for deletion by determining the node y to actually delete.
 *        3) If z has no children or only one child,
 *           transplant it with its child.
 *        4) If z has two children, find its successor y,
 *           transplant z with y, and copy y's left child to z's left.
 *        5) If the original color of y was black,
 *           fix up the tree to maintain Red-Black properties.
 *        6) Free the memory of the deleted node z.
 *
 * @param t    The Red-Black Tree.
 * @param key  The key of the node to delete.
 */
void rb_tree_delete(RBTree *t, int key) {
    RBNode *z = t->root;

    // 1) Find node z (the node to delete)
    while (z != t->nil && z->key != key) {
        if (key < z->key) {
            // Go left if key is less than z's key
            z = z->left;
        } else {
            // Go right otherwise
            z = z->right;
        }
    }
    if (z == t->nil) {
        // Key not found, nothing to delete
        return;
    }

    // 2) Prepare for deletion
    RBNode *y = z; // Node to actually delete
    Color y_original_color = y->color;
    RBNode *x;

    if (z->left == t->nil) {
        // 3a-1) z only has right child or no children
        x = z->right;
        rb_tree_transplant(t, z, z->right);
    } else if (z->right == t->nil) {
        // 3a-2) z only has left child or no children
        x = z->left;
        rb_tree_transplant(t, z, z->left);
    } else {
        // 3b) z has two children.
        //     find successor y = min(z->right)
        y = rb_tree_minimum(t, z->right);
        y_original_color = y->color;
        x = y->right; // x is the right child of y (can be nil)

        if (y->parent == z) {
            // If the successor is a direct child of z,
            // we can just link x to y.
            x->parent = y;
        } else {
            // If not, transplant y with its right child and
            // link y's right child to y's parent.
            rb_tree_transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        // Move y into z's position
        rb_tree_transplant(t, z, y);
        y->left = z->left;   // Copy left child
        y->left->parent = y; // Update parent pointer
        y->color = z->color; // Copy color from z
    }

    // 4) Fixup if we removed a black node.
    //    If we deleted a black node, the black height property may be violated.
    if (y_original_color == BLACK) {
        rb_tree_delete_fixup(t, x);
    }

    // 5) Free the deleted node.
    //    Don't forget to free the memory! >_<
    free(z);
}

/**
 * @brief Fix up the Red-Black Tree after deletion.
 *        This function is called after rb_tree_delete().
 *
 * This handles the “double-black” cases:
 *   1) x is the new root or x is red -> recolor x black, done.
 *   2) x’s sibling w is red -> rotate to turn w black, then continue.
 *   3) w is black with two black children -> recolor w red, move up to parent.
 *   4) w is black with 1 or more red children
 *      -> perform appropriate rotations/recoloring
 *         to eliminate extra black on x.
 *
 * @param t  The Red-Black Tree.
 * @param x  The node that may violate properties after deletion.
 */
static void rb_tree_delete_fixup(RBTree *t, RBNode *x) {
    while (x != t->root && x->color == BLACK) {
        if (x == x->parent->left) {
            // w is the sibling of x.
            // It will be used for fixing the tree.
            RBNode *w = x->parent->right;

            if (w->color == RED) {
                // 1) If sibling is red, rotate and make sibling black
                w->color = BLACK;
                x->parent->color = RED;
                rb_tree_left_rotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // 2) If sibling has two black-colored children nodes
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // 3) If w->left is red and w->right is black,
                    //    rotate right and recolor
                    w->left->color = BLACK;
                    w->color = RED;
                    rb_tree_right_rotate(t, w);
                    w = x->parent->right;
                }
                // 4) If w->right is red, rotate left and recolor
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rb_tree_left_rotate(t, x->parent);
                x = t->root;
            }
        } else {
            // Mirror case: x is right child
            RBNode *w = x->parent->left;

            if (w->color == RED) {
                // 1') If sibling is red, rotate and make sibling black
                w->color = BLACK;
                x->parent->color = RED;
                rb_tree_right_rotate(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                // 2') If sibling has two black-colored children nodes
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    // 3') If w->right is red and w->left is black,
                    //     rotate left and recolor
                    w->right->color = BLACK;
                    w->color = RED;
                    rb_tree_left_rotate(t, w);
                    w = x->parent->left;
                }
                // 4') If w->left is red, rotate right and recolor
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rb_tree_right_rotate(t, x->parent);
                x = t->root;
            }
        }
    }

    // Ensure root is always black (Don't forget this! >_<)
    // It is important because the root must always be black!
    x->color = BLACK;
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

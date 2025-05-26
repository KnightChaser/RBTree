// src/main.c
#include "../include/rb_tree.h"
#include <stdio.h>
#include <stdlib.h>

static void print_node(RBTree *t, RBNode *n) {
    if (n == t->nil)
        printf("nil");
    else
        printf("%d(%s)", n->key, n->color == RED ? "R" : "B");
}

static void inorder_traverse(RBTree *t, RBNode *n) {
    if (n == t->nil)
        return;
    inorder_traverse(t, n->left);
    print_node(t, n);
    printf(" ");
    inorder_traverse(t, n->right);
}

int main(void) {
    RBTree *t = rb_tree_create();
    if (!t) {
        fprintf(stderr, "Failed to create RBTree\n");
        return EXIT_FAILURE;
    }

    // 1) Rotation Demo
    RBNode *x = calloc(1, sizeof *x);
    RBNode *y = calloc(1, sizeof *y);
    if (!x || !y) {
        fprintf(stderr, "Alloc failed\n");
        free(x);
        free(y);
        rb_tree_destroy(t);
        return EXIT_FAILURE;
    }

    x->key = 1;
    x->color = RED;
    y->key = 2;
    y->color = RED;
    x->parent = t->nil;
    t->root = x;
    x->left = t->nil;
    x->right = y;
    y->parent = x;
    y->left = t->nil;
    y->right = t->nil;

    printf("Before left_rotate  => root=%d\n", t->root->key);
    rb_tree_left_rotate(t, x);
    printf(" After left_rotate  => root=%d\n\n", t->root->key);

    printf("Before right_rotate => root=%d\n", t->root->key);
    rb_tree_right_rotate(t, y);
    printf(" After right_rotate => root=%d\n\n", t->root->key);

    free(x);
    free(y);

    // **RESET** the tree so root no longer points at freed memory
    t->root = t->nil;

    // 2) Insertion Demo
    int keys[] = {10, 20, 30, 15, 25, 5};
    for (size_t i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
        printf("Insert %d => In-order: ", keys[i]);
        rb_tree_insert(t, keys[i]);
        inorder_traverse(t, t->root);
        printf("\n");
    }

    rb_tree_destroy(t);
    return EXIT_SUCCESS;
}

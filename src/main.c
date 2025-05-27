// src/main.c
#include "../include/auxiliary.h"
#include "../include/rb_tree.h"
#include <stdio.h>
#include <stdlib.h>

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

    printf("Before left_rotate  => root = %d\n", t->root->key);
    rb_tree_left_rotate(t, x);
    printf(" After left_rotate  => root = %d\n\n", t->root->key);

    printf("Before right_rotate => root = %d\n", t->root->key);
    rb_tree_right_rotate(t, y);
    printf(" After right_rotate => root = %d\n\n", t->root->key);

    free(x);
    free(y);
    t->root = t->nil; // clear out dangling root

    // 2) Insertion Demo
    int keys[] = {10, 20, 30, 15, 25, 5, 40, 100, -5};
    size_t nk = sizeof(keys) / sizeof(*keys);
    for (size_t i = 0; i < nk; i++) {
        printf("Insert %d => In-order: ", keys[i]);
        rb_tree_insert(t, keys[i]);
        inorder_traverse(t, t->root);
        printf("\n");
    }

    // 3) Deletion Demo
    int del_keys[] = {15, 10, 20, 5, 30, 25};
    size_t nd = sizeof(del_keys) / sizeof(*del_keys);
    for (size_t i = 0; i < nd; i++) {
        printf("Delete %d => In-order: ", del_keys[i]);
        rb_tree_delete(t, del_keys[i]);
        inorder_traverse(t, t->root);
        printf("\n");
    }

    rb_tree_destroy(t);
    return EXIT_SUCCESS;
}

// src/main.c
#include "../include/rb_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    RBTree *t = rb_tree_create();

    RBNode *x = calloc(1, sizeof(RBNode));
    RBNode *y = calloc(1, sizeof(RBNode));
    if (!t || !x || !y) {
        fprintf(stderr, "Memory allocation failed\n");
        free(x);
        free(y);
        rb_tree_destroy(t);
        return EXIT_FAILURE;
    }

    x->key = 1;
    x->color = RED;
    y->key = 2;
    y->color = RED;

    // link them
    x->parent = t->nil;
    t->root = x;
    x->left = t->nil;
    x->right = y;
    y->parent = x;
    y->left = t->nil;
    y->right = t->nil;

    printf("Before rb_tree_left_rotate() => root = %d\n", t->root->key);
    rb_tree_left_rotate(t, x);
    printf("After rb_tree_left_rotate() => root = %d\n", t->root->key);

    printf("Before rb_tree_right_rotate() => root = %d\n", t->root->key);
    rb_tree_right_rotate(t, y);
    printf("After rb_tree_right_rotate() => root = %d\n", t->root->key);

    // Clean up
    free(x);
    free(y);
    rb_tree_destroy(t);

    return EXIT_SUCCESS;
}

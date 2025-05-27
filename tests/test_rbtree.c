// tests/test_rbtree.c
#include "../include/auxiliary.h"
#include "../include/rb_tree.h"
#include <assert.h>
#include <stdio.h>

static void test_insert_search_delete(void) {
    RBTree *t = rb_tree_create();
    assert(t);

    int keys[] = {50, 20, 70, 10, 30, 60, 80};
    for (size_t i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
        rb_tree_insert(t, keys[i]);
        // after insert, search must find the node
        RBNode *n = rb_tree_search(t, keys[i]);
        assert(n != t->nil && n->key == keys[i]);
    }

    // verify tree structure via inorder must be sorted
    printf("Tree after inserts: ");
    inorder_traverse(t, t->root);
    printf("\n");

    // now delete half the keys
    int del[] = {20, 70, 10};
    for (size_t i = 0; i < sizeof(del) / sizeof(*del); i++) {
        rb_tree_delete(t, del[i]);
        // after delete, search must not find it
        RBNode *n = rb_tree_search(t, del[i]);
        assert(n == t->nil);
    }

    printf("Tree after deletes: ");
    inorder_traverse(t, t->root);
    printf("\n");

    rb_tree_destroy(t);
}

int main(void) {
    test_insert_search_delete();
    puts("ALL TESTS PASSED.");
    return 0;
}

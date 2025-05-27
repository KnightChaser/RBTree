// src/main.c
#include "../include/auxiliary.h"
#include "../include/rb_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SZ 128

static void print_help(void) {
    puts("Commands:");
    puts("  insert <key>   — insert a key");
    puts("  delete <key>   — delete a key");
    puts("  print          — in-order dump of the tree");
    puts("  help           — show this message");
    puts("  exit           — quit");
}

int main(void) {
    RBTree *t = rb_tree_create();
    if (!t) {
        fprintf(stderr, "Failed to create RBTree\n");
        return EXIT_FAILURE;
    }

    char line[LINE_SZ];
    print_help();

    while (1) {
        printf("> ");
        if (!fgets(line, sizeof line, stdin)) {
            putchar('\n');
            break;
        }

        // trim newline
        line[strcspn(line, "\r\n")] = 0;
        char *cmd = strtok(line, " \t");
        if (!cmd)
            continue;

        if (strcmp(cmd, "insert") == 0) {
            char *arg = strtok(NULL, " \t");
            if (!arg) {
                printf("Usage: insert <key>\n");
                continue;
            }
            int key = atoi(arg);
            rb_tree_insert(t, key);
            printf("Inserted %d\n", key);

        } else if (strcmp(cmd, "delete") == 0) {
            char *arg = strtok(NULL, " \t");
            if (!arg) {
                printf("Usage: delete <key>\n");
                continue;
            }
            int key = atoi(arg);
            rb_tree_delete(t, key);
            printf("Deleted %d (if it existed)\n", key);

        } else if (strcmp(cmd, "print") == 0) {
            printf("In-order: ");
            inorder_traverse(t, t->root);
            printf("\n");

        } else if (strcmp(cmd, "help") == 0) {
            print_help();

        } else if (strcmp(cmd, "exit") == 0) {
            break;

        } else {
            printf("Unknown command: '%s'  (type 'help')\n", cmd);
        }
    }

    rb_tree_destroy(t);
    return EXIT_SUCCESS;
}

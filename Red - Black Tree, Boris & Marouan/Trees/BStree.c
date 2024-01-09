#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* p;
    struct node* r;
    struct node* l;
};

struct node* root = NULL;

struct node* bst(struct node* curr,
                      struct node* node_t) {

    // :) Base case :
    // If the tree is empty,
    // return a new node
    if (curr == NULL) {
        return node_t;
    }

    // Otherwise recur down the tree
    if (node_t->value < curr->value)  {
        curr->l = bst(curr->l, node_t);
        curr->l->p = curr;

    } else if (node_t->value > curr->value) {
        curr->r = bst(curr->r, node_t);
        curr->r->p = curr;
    }

    return curr;
}

void levelorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct node* queue[1000];
    int front = 0;
    int rear = 0;

    // Enqueue root and a NULL as marker
    queue[rear++] = root;
    queue[rear++] = NULL; // NULL as a marker for end of level

    while (front < rear) {
        struct node* curr = queue[front++];

        if (curr == NULL) {
            // End of a level
            printf("\n");
            if (front < rear) { // Queue is not empty, add another level marker
                queue[rear++] = NULL;
            }
        } else {
            // Print curr node and its parent
            if (curr->p != NULL) {
                printf("%d (parent: %d) ", curr->value, curr->p->value);
            } else {
                printf("%d (root) ", curr->value); // Root node
            }

            if (curr->l != NULL)
                queue[rear++] = curr->l;
            if (curr->r != NULL)
                queue[rear++] = curr->r;
        }
    }
}

int main(void) {
    int a[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
            10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    for (int i = 0; i < (sizeof(a) / sizeof(int)); i++) {

        // allocating memory to the node and initializing:
        // 1. color as red
        // 2. parent, left and right pointers as NULL
        // 3. data as i-th value in the array
        struct node* node_t
            = (struct node*)malloc(sizeof(struct node));

        node_t->r = NULL;
        node_t->l = NULL;
        node_t->p = NULL;
        node_t->value = a[i];

        root = bst(root, node_t);

    }

    printf("Level order traversal of BS tree\n\n");
    levelorder(root);
    printf("\n");

    return 0;
}
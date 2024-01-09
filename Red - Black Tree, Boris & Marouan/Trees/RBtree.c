#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    int colour; // 1-red, 0-black
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

void rightrotate(struct node* node_t) {
    struct node* left = node_t->l;
    node_t->l = left->r;

    if (node_t->l) {
        node_t->l->p = node_t;
    }
    left->p = node_t->p;

    if (!node_t->p) {
        root = left;
    } else if (node_t == node_t->p->l) {
        node_t->p->l = left;
    } else {
        node_t->p->r = left;
    }

    left->r = node_t;
    node_t->p = left;
}

void leftrotate(struct node* node_t) {
    struct node* right = node_t->r;
    node_t->r = right->l;

    if (node_t->r) {
        node_t->r->p = node_t;
    }
    right->p = node_t->p;

    if (!node_t->p) {
        root = right;
    } else if (node_t == node_t->p->l) {
        node_t->p->l = right;
    } else {
        node_t->p->r = right;
    }

    right->l = node_t;
    node_t->p = right;
}

void fixup(struct node* root, struct node* curr) {
    struct node* parent_curr = NULL;
    struct node* grand_parent_curr = NULL;

    while ((curr != root) && (curr->colour != 0)
           && (curr->p->colour == 1)) {

        parent_curr = curr->p;
        grand_parent_curr = curr->p->p;

        /*  Case : A
             Parent of curr is left child
             of Grand-parent of
           curr */
        if (parent_curr == grand_parent_curr->l) {

            struct node* uncle_curr = grand_parent_curr->r;

            /* Case : 1
                The uncle of curr is also red
                Only Recoloring required */
            if (uncle_curr != NULL && uncle_curr->colour == 1) {
                grand_parent_curr->colour = 1;
                parent_curr->colour = 0;
                uncle_curr->colour = 0;
                curr = grand_parent_curr;

            } else {

                /* Case : 2
                     curr is right child of its parent
                     Left-rotation required.

                     Left-Right*/
                if (curr == parent_curr->r) {
                    leftrotate(parent_curr);
                    curr = parent_curr;
                    parent_curr = curr->p;
                }

                /* Case : 3
                     curr is left child of its parent
                     Right-rotation required.

                     Left-Left*/
                rightrotate(grand_parent_curr);
                int t = parent_curr->colour;
                parent_curr->colour = grand_parent_curr->colour;
                grand_parent_curr->colour = t;
                curr = parent_curr;
            }
        }

        /* Case : B
             Parent of curr is right
             child of Grand-parent of
           curr */
        else {
            struct node* uncle_curr = grand_parent_curr->l;

            /*  Case : 1
                The uncle of curr is also red
                Only Recoloring required */
            if ((uncle_curr != NULL) && (uncle_curr->colour == 1)) {
                grand_parent_curr->colour = 1;
                parent_curr->colour = 0;
                uncle_curr->colour = 0;
                curr = grand_parent_curr;

            } else {

                /* Case : 2
                   curr is left child of its parent
                   Right-rotation required.

                   Right-Left*/
                if (curr == parent_curr->l) {
                    rightrotate(parent_curr);
                    curr = parent_curr;
                    parent_curr = curr->p;
                }

                /* Case : 3
                     curr is right child of its parent
                     Left-rotation required.

                     Right-Right*/
                leftrotate(grand_parent_curr);
                int t = parent_curr->colour;
                parent_curr->colour = grand_parent_curr->colour;
                grand_parent_curr->colour = t;
                curr = parent_curr;
            }
        }
    }
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
        node_t->colour = 1;

        root = bst(root, node_t);

        fixup(root, node_t);
        root->colour = 0;
    }

    printf("Level order traversal of RB tree:\n\n");
    levelorder(root);
    printf("\n");

    return 0;
}
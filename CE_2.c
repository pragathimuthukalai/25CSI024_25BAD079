//Class Exercise 2
//This program creates a self-balancing AVL tree containing key-code pairs, displays them in sorted order using
//inorder traversal, deletes the minimum key, rebalances the tree, and displays the remaining elements.
// You are using GCC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    int key, h;
    char code[32];
    struct Node *l, *r;
} Node;
int height(Node *p) {
    return p ? p->h : 0;
}
int max(int a, int b) {
    return a > b ? a : b;
}
Node* create(int key, char code[]) {
    Node *p = malloc(sizeof(Node));
    p->key = key;
    strcpy(p->code, code);
    p->h = 1;
    p->l = p->r = NULL;
    return p;
}
Node* rightRotate(Node *y) {
    Node *x = y->l, *t = x->r;
    x->r = y;
    y->l = t;
    y->h = 1 + max(height(y->l), height(y->r));
    x->h = 1 + max(height(x->l), height(x->r));
    return x;
}
Node* leftRotate(Node *x) {
    Node *y = x->r, *t = y->l;
    y->l = x;
    x->r = t;
    x->h = 1 + max(height(x->l), height(x->r));
    y->h = 1 + max(height(y->l), height(y->r));
    return y;
}
int balance(Node *p) {
    return p ? height(p->l) - height(p->r) : 0;
}
Node* insert(Node *root, int key, char code[]) {
    if (!root) return create(key, code);
    if (key < root->key)
        root->l = insert(root->l, key, code);
    else
        root->r = insert(root->r, key, code);
    root->h = 1 + max(height(root->l), height(root->r));
    int b = balance(root);
    if (b > 1 && key < root->l->key)
        return rightRotate(root);
    if (b < -1 && key > root->r->key)
        return leftRotate(root);
    if (b > 1 && key > root->l->key) {
        root->l = leftRotate(root->l);
        return rightRotate(root);
    }
    if (b < -1 && key < root->r->key) {
        root->r = rightRotate(root->r);
        return leftRotate(root);
    }
    return root;
}
Node* deleteMin(Node *root) {
    if (!root->l) {
        Node *t = root->r;
        free(root);
        return t;
    }
    root->l = deleteMin(root->l);
    root->h = 1 + max(height(root->l), height(root->r));
    int b = balance(root);
    if (b > 1 && balance(root->l) >= 0)
        return rightRotate(root);
    if (b > 1) {
        root->l = leftRotate(root->l);
        return rightRotate(root);
    }
    if (b < -1 && balance(root->r) <= 0)
        return leftRotate(root);
    if (b < -1) {
        root->r = rightRotate(root->r);
        return leftRotate(root);
    }
    return root;
}
void inorder(Node *root) {
    if (root) {
        inorder(root->l);
        printf("%d %s\n", root->key, root->code);
        inorder(root->r);
    }
}
int main() {
    int n, key;
    char code[32];
    Node *root = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &key, code);
        root = insert(root, key, code);
    }
    printf("In-order traversal before deletion:\n");
    inorder(root);
    root = deleteMin(root);
    printf("In-order traversal after deletion:\n");
    inorder(root);
    return 0;
}
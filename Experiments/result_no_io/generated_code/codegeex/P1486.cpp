#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

Node *root = NULL;
int total = 0, leave = 0, min;

void insert(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->left = node->right = NULL;
    if (root == NULL) {
        root = node;
        return;
    }
    Node *cur = root;
    while (1) {
        if (val > cur->val) {
            if (cur->right == NULL) {
                cur->right = node;
                return;
            }
            cur = cur->right;
        } else {
            if (cur->left == NULL) {
                cur->left = node;
                return;
            }
            cur = cur->left;
        }
    }
}

void add(int val) {
    Node *cur = root;
    while (cur != NULL) {
        if (cur->val + val >= min) {
            cur = cur->right;
        } else {
            leave++;
            cur = cur->left;
        }
    }
}

void subtract(int val) {
    Node *cur = root;
    while (cur != NULL) {
        if (cur->val - val >= min) {
            cur = cur->right;
        } else {
            leave++;
            cur = cur->left;
        }
    }
}

int find_kth(int k) {
    Node *cur = root;
    while (cur != NULL) {
        int left_count = 0;
        Node *tmp = cur->left;
        while (tmp != NULL) {
            left_count++;
            tmp = tmp->right;
        }
        if (k == left_count) {
            return cur->val;
        } else if (k < left_count) {
            cur = cur->left;
        } else {
            k -= left_count + 1;
            cur = cur->right;
        }
    }
    return -1;
}

int main() {
    int n;
    scanf("%d %d", &n, &min);
    for (int i = 0; i < n; i++) {
        char op;
        int k;
        scanf(" %c %d", &op, &k);
        if (op == 'I') {
            if (k >= min) {
                insert(k);
                total++;
            }
        } else if (op == 'A') {
            add(k);
        } else if (op == 'S') {
            subtract(k);
        } else if (op == 'F') {
            int result = find_kth(k);
            if (result == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", result);
            }
        }
    }
    printf("%d\n", leave);
    return 0;
}
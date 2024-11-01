#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define INF 0x3f3f3f3f

typedef struct Node {
    int val, size, sum, max_sum, lmax, rmax, lazy, rev;
    struct Node *left, *right;
} Node;

Node *newNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->size = 1;
    node->sum = val;
    node->max_sum = val;
    node->lmax = val;
    node->rmax = val;
    node->lazy = INF;
    node->rev = 0;
    node->left = node->right = NULL;
    return node;
}

void pushUp(Node *node) {
    if (!node) return;
    Node *l = node->left, *r = node->right;
    node->size = (l ? l->size : 0) + (r ? r->size : 0) + 1;
    node->sum = (l ? l->sum : 0) + (r ? r->sum : 0) + node->val;
    node->lmax = l ? (l->lmax > l->sum + node->val + (r ? r->lmax : 0) ? l->lmax : l->sum + node->val + (r ? r->lmax : 0)) : (node->val + (r ? r->lmax : 0));
    node->rmax = r ? (r->rmax > r->sum + node->val + (l ? l->rmax : 0) ? r->rmax : r->sum + node->val + (l ? l->rmax : 0)) : (node->val + (l ? l->rmax : 0));
    node->max_sum = node->val;
    if (l) node->max_sum = node->max_sum > l->max_sum ? node->max_sum : l->max_sum;
    if (r) node->max_sum = node->max_sum > r->max_sum ? node->max_sum : r->max_sum;
    if (l && r) {
        int tmp = l->rmax + node->val + r->lmax;
        node->max_sum = node->max_sum > tmp ? node->max_sum : tmp;
    }
}

void pushDown(Node *node) {
    if (!node) return;
    if (node->lazy != INF) {
        if (node->left) {
            node->left->val = node->lazy;
            node->left->sum = node->lazy * node->left->size;
            node->left->max_sum = node->left->lmax = node->left->rmax = node->lazy > 0 ? node->left->sum : node->lazy;
            node->left->lazy = node->lazy;
        }
        if (node->right) {
            node->right->val = node->lazy;
            node->right->sum = node->lazy * node->right->size;
            node->right->max_sum = node->right->lmax = node->right->rmax = node->lazy > 0 ? node->right->sum : node->lazy;
            node->right->lazy = node->lazy;
        }
        node->lazy = INF;
    }
    if (node->rev) {
        Node *tmp = node->left;
        node->left = node->right;
        node->right = tmp;
        if (node->left) node->left->rev ^= 1;
        if (node->right) node->right->rev ^= 1;
        int tmp_lmax = node->lmax, tmp_rmax = node->rmax;
        node->lmax = tmp_rmax;
        node->rmax = tmp_lmax;
        node->rev = 0;
    }
}

Node *merge(Node *a, Node *b) {
    if (!a) return b;
    if (!b) return a;
    if (rand() % (a->size + b->size) < a->size) {
        pushDown(a);
        a->right = merge(a->right, b);
        pushUp(a);
        return a;
    } else {
        pushDown(b);
        b->left = merge(a, b->left);
        pushUp(b);
        return b;
    }
}

void split(Node *node, int k, Node **a, Node **b) {
    if (!node) {
        *a = *b = NULL;
        return;
    }
    pushDown(node);
    if (k <= (node->left ? node->left->size : 0)) {
        *b = node;
        split(node->left, k, a, &((*b)->left));
        pushUp(*b);
    } else {
        *a = node;
        split(node->right, k - (node->left ? node->left->size : 0) - 1, &((*a)->right), b);
        pushUp(*a);
    }
}

Node *build(int *arr, int n) {
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = merge(root, newNode(arr[i]));
    }
    return root;
}

void insert(Node **root, int pos, int *arr, int n) {
    Node *a, *b;
    split(*root, pos, &a, &b);
    *root = merge(a, merge(build(arr, n), b));
}

void delete(Node **root, int pos, int n) {
    Node *a, *b, *c;
    split(*root, pos - 1, &a, &b);
    split(b, n, &b, &c);
    *root = merge(a, c);
}

void makeSame(Node **root, int pos, int n, int c) {
    Node *a, *b, *c;
    split(*root, pos - 1, &a, &b);
    split(b, n, &b, &c);
    b->val = c;
    b->sum = c * b->size;
    b->max_sum = b->lmax = b->rmax = c > 0 ? b->sum : c;
    b->lazy = c;
    *root = merge(a, merge(b, c));
}

void reverse(Node **root, int pos, int n) {
    Node *a, *b, *c;
    split(*root, pos - 1, &a, &b);
    split(b, n, &b, &c);
    b->rev ^= 1;
    *root = merge(a, merge(b, c));
}

int getSum(Node **root, int pos, int n) {
    Node *a, *b, *c;
    split(*root, pos - 1, &a, &b);
    split(b, n, &b, &c);
    int sum = b->sum;
    *root = merge(a, merge(b, c));
    return sum;
}

int maxSum(Node *root) {
    return root->max_sum;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    Node *root = build(arr, N);
    char op[20];
    int pos, tot, c;
    for (int i = 0; i < M; i++) {
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            scanf("%d %d", &pos, &tot);
            int *newArr = (int *)malloc(sizeof(int) * tot);
            for (int j = 0; j < tot; j++) {
                scanf("%d", &newArr[j]);
            }
            insert(&root, pos, newArr, tot);
            free(newArr);
        } else if (strcmp(op, "DELETE") == 0) {
            scanf("%d %d", &pos, &tot);
            delete(&root, pos, tot);
        } else if (strcmp(op, "MAKE-SAME") == 0) {
            scanf("%d %d %d", &pos, &tot, &c);
            makeSame(&root, pos, tot, c);
        } else if (strcmp(op, "REVERSE") == 0) {
            scanf("%d %d", &pos, &tot);
            reverse(&root, pos, tot);
        } else if (strcmp(op, "GET-SUM") == 0) {
            scanf("%d %d", &pos, &tot);
            printf("%d\n", getSum(&root, pos, tot));
        } else if (strcmp(op, "MAX-SUM") == 0) {
            printf("%d\n", maxSum(root));
        }
    }
    free(arr);
    return 0;
}
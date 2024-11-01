#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define INF 1000000000

typedef struct Node {
    int val, size, sum, max_sum, lmax, rmax, lazy, rev;
    struct Node *left, *right;
} Node;

Node *new_node(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = node->sum = node->max_sum = node->lmax = node->rmax = val;
    node->size = 1;
    node->lazy = INF;
    node->rev = 0;
    node->left = node->right = NULL;
    return node;
}

void update(Node *node) {
    if (!node) return;
    node->size = 1;
    node->sum = node->val;
    node->lmax = node->rmax = node->max_sum = node->val;
    if (node->left) {
        node->size += node->left->size;
        node->sum += node->left->sum;
        node->lmax = node->left->lmax > (node->left->sum + node->val) ? node->left->lmax : (node->left->sum + node->val);
        node->rmax = node->left->rmax > (node->left->sum + node->val) ? node->left->rmax : (node->left->sum + node->val);
        node->max_sum = node->left->max_sum > (node->left->rmax + node->val) ? node->left->max_sum : (node->left->rmax + node->val);
    }
    if (node->right) {
        node->size += node->right->size;
        node->sum += node->right->sum;
        node->rmax = node->right->rmax > (node->right->sum + node->val) ? node->right->rmax : (node->right->sum + node->val);
        node->lmax = node->right->lmax > (node->right->sum + node->val) ? node->right->lmax : (node->right->sum + node->val);
        node->max_sum = node->right->max_sum > (node->right->lmax + node->val) ? node->right->max_sum : (node->right->lmax + node->val);
    }
}

void push_down(Node *node) {
    if (!node) return;
    if (node->lazy != INF) {
        if (node->left) {
            node->left->lazy = node->left->val = node->lazy;
            node->left->sum = node->left->size * node->lazy;
            node->left->lmax = node->left->rmax = node->left->max_sum = node->left->sum > 0 ? node->left->sum : 0;
        }
        if (node->right) {
            node->right->lazy = node->right->val = node->lazy;
            node->right->sum = node->right->size * node->lazy;
            node->right->lmax = node->right->rmax = node->right->max_sum = node->right->sum > 0 ? node->right->sum : 0;
        }
        node->lazy = INF;
    }
    if (node->rev) {
        Node *tmp = node->left;
        node->left = node->right;
        node->right = tmp;
        if (node->left) node->left->rev ^= 1;
        if (node->right) node->right->rev ^= 1;
        node->rev = 0;
    }
}

Node *merge(Node *left, Node *right) {
    if (!left) return right;
    if (!right) return left;
    if (rand() % (left->size + right->size) < left->size) {
        push_down(left);
        left->right = merge(left->right, right);
        update(left);
        return left;
    } else {
        push_down(right);
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

void split(Node *root, int k, Node **left, Node **right) {
    if (!root) {
        *left = *right = NULL;
        return;
    }
    push_down(root);
    if (k <= (root->left ? root->left->size : 0)) {
        *right = root;
        split(root->left, k, left, &((*right)->left));
        update(*right);
    } else {
        *left = root;
        split(root->right, k - (root->left ? root->left->size : 0) - 1, &((*left)->right), right);
        update(*left);
    }
}

void insert(Node **root, int pos, int tot, int *vals) {
    Node *left, *right, *mid = NULL;
    for (int i = 0; i < tot; i++) {
        mid = merge(mid, new_node(vals[i]));
    }
    split(*root, pos, &left, &right);
    *root = merge(merge(left, mid), right);
}

void delete(Node **root, int pos, int tot) {
    Node *left, *mid, *right;
    split(*root, pos - 1, &left, &mid);
    split(mid, tot, &mid, &right);
    *root = merge(left, right);
}

void make_same(Node **root, int pos, int tot, int c) {
    Node *left, *mid, *right;
    split(*root, pos - 1, &left, &mid);
    split(mid, tot, &mid, &right);
    mid->lazy = mid->val = c;
    mid->sum = mid->size * c;
    mid->lmax = mid->rmax = mid->max_sum = mid->sum > 0 ? mid->sum : 0;
    *root = merge(merge(left, mid), right);
}

void reverse(Node **root, int pos, int tot) {
    Node *left, *mid, *right;
    split(*root, pos - 1, &left, &mid);
    split(mid, tot, &mid, &right);
    mid->rev ^= 1;
    *root = merge(merge(left, mid), right);
}

int get_sum(Node **root, int pos, int tot) {
    Node *left, *mid, *right;
    split(*root, pos - 1, &left, &mid);
    split(mid, tot, &mid, &right);
    int sum = mid->sum;
    *root = merge(merge(left, mid), right);
    return sum;
}

int max_sum(Node *root) {
    if (!root) return 0;
    push_down(root);
    return root->max_sum;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    Node *root = NULL;
    for (int i = 0; i < N; i++) {
        int val;
        scanf("%d", &val);
        root = merge(root, new_node(val));
    }
    for (int i = 0; i < M; i++) {
        char op[20];
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            int *vals = (int *)malloc(tot * sizeof(int));
            for (int j = 0; j < tot; j++) {
                scanf("%d", &vals[j]);
            }
            insert(&root, pos, tot, vals);
            free(vals);
        } else if (strcmp(op, "DELETE") == 0) {
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            delete(&root, pos, tot);
        } else if (strcmp(op, "MAKE-SAME") == 0) {
            int pos, tot, c;
            scanf("%d %d %d", &pos, &tot, &c);
            make_same(&root, pos, tot, c);
        } else if (strcmp(op, "REVERSE") == 0) {
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            reverse(&root, pos, tot);
        } else if (strcmp(op, "GET-SUM") == 0) {
            int pos, tot;
            scanf("%d %d", &pos, &tot);
            printf("%d\n", get_sum(&root, pos, tot));
        } else if (strcmp(op, "MAX-SUM") == 0) {
            printf("%d\n", max_sum(root));
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int lazy;
    int min;
    int sum;
} Node;

Node tree[800000];

void build(int node, int start, int end) {
    tree[node].start = start;
    tree[node].end = end;
    tree[node].lazy = 0;
    if (start == end) {
        scanf("%d", &tree[node].min);
        tree[node].sum = tree[node].min;
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node].min = tree[2 * node].min < tree[2 * node + 1].min ? tree[2 * node].min : tree[2 * node + 1].min;
        tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    }
}

void push_down(int node) {
    if (tree[node].lazy != 0) {
        tree[2 * node].lazy += tree[node].lazy;
        tree[2 * node + 1].lazy += tree[node].lazy;
        tree[2 * node].min += tree[node].lazy;
        tree[2 * node + 1].min += tree[node].lazy;
        tree[2 * node].sum += tree[node].lazy * (tree[2 * node].end - tree[2 * node].start + 1);
        tree[2 * node + 1].sum += tree[node].lazy * (tree[2 * node + 1].end - tree[2 * node + 1].start + 1);
        tree[node].lazy = 0;
    }
}

void update(int node, int start, int end, int value) {
    if (tree[node].start > end || tree[node].end < start) {
        return;
    }
    if (tree[node].start >= start && tree[node].end <= end) {
        tree[node].lazy += value;
        tree[node].min += value;
        tree[node].sum += value * (tree[node].end - tree[node].start + 1);
        return;
    }
    push_down(node);
    update(2 * node, start, end, value);
    update(2 * node + 1, start, end, value);
    tree[node].min = tree[2 * node].min < tree[2 * node + 1].min ? tree[2 * node].min : tree[2 * node + 1].min;
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
}

int query_min(int node, int start, int end) {
    if (tree[node].start > end || tree[node].end < start) {
        return 100000;
    }
    if (tree[node].start >= start && tree[node].end <= end) {
        return tree[node].min;
    }
    push_down(node);
    int left_min = query_min(2 * node, start, end);
    int right_min = query_min(2 * node + 1, start, end);
    return left_min < right_min ? left_min : right_min;
}

int query_sum(int node, int start, int end) {
    if (tree[node].start > end || tree[node].end < start) {
        return 0;
    }
    if (tree[node].start >= start && tree[node].end <= end) {
        return tree[node].sum;
    }
    push_down(node);
    return query_sum(2 * node, start, end) + query_sum(2 * node + 1, start, end);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    build(1, 1, n);
    char op;
    int a, b, c;
    for (int i = 0; i < q; i++) {
        scanf(" %c", &op);
        if (op == 'M') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query_min(1, a, b));
        } else if (op == 'S') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query_sum(1, a, b));
        } else if (op == 'P') {
            scanf("%d %d %d", &a, &b, &c);
            update(1, a, b, c);
        }
    }
    return 0;
}
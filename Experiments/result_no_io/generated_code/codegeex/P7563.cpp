#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int left;
    int right;
    int min_cost;
} Node;

Node tree[800005];
int arr[200005];
int lazy[800005];
int n;

void build(int node, int start, int end) {
    tree[node].left = start;
    tree[node].right = end;
    if (start == end) {
        tree[node].min_cost = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node].min_cost = tree[2 * node].min_cost + tree[2 * node + 1].min_cost;
    }
}

void update(int node, int start, int end, int value) {
    if (lazy[node] != 0) {
        tree[node].min_cost += (tree[node].right - tree[node].left + 1) * lazy[node];
        if (tree[node].left != tree[node].right) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > end || start > tree[node].right || end < tree[node].left) {
        return;
    }
    if (start <= tree[node].left && tree[node].right <= end) {
        tree[node].min_cost += (tree[node].right - tree[node].left + 1) * value;
        if (tree[node].left != tree[node].right) {
            lazy[2 * node] += value;
            lazy[2 * node + 1] += value;
        }
        return;
    }
    update(2 * node, start, end, value);
    update(2 * node + 1, start, end, value);
    tree[node].min_cost = tree[2 * node].min_cost + tree[2 * node + 1].min_cost;
}

int query(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node].min_cost += (tree[node].right - tree[node].left + 1) * lazy[node];
        if (tree[node].left != tree[node].right) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (start > end || start > tree[node].right || end < tree[node].left) {
        return 0;
    }
    if (start <= tree[node].left && tree[node].right <= end) {
        return tree[node].min_cost;
    }
    return query(2 * node, start, end) + query(2 * node + 1, start, end);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, h, c;
        scanf("%d %d %d", &a, &h, &c);
        arr[a] = c;
    }
    build(1, 1, n);
    int total_cost = 0;
    for (int i = 2; i <= n; i++) {
        int cost = query(1, 1, i - 1);
        if (cost > arr[i]) {
            update(1, 1, i - 1, arr[i] - cost);
        }
        total_cost += query(1, 1, i - 1);
    }
    printf("%d\n", total_cost);
    return 0;
}
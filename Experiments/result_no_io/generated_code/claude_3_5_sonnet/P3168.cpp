#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 100005

typedef struct {
    int start, end, priority;
} Task;

typedef struct {
    int priority;
    int count;
} PriorityCount;

Task tasks[MAX_M];
PriorityCount priorityCounts[MAX_N];
int tree[MAX_N * 4];
int lazy[MAX_N * 4];

int cmp(const void *a, const void *b) {
    return ((PriorityCount*)a)->priority - ((PriorityCount*)b)->priority;
}

void push_down(int node, int l, int r) {
    if (lazy[node]) {
        tree[node] += lazy[node] * (r - l + 1);
        if (l != r) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int start, int end, int val) {
    push_down(node, l, r);
    if (start > r || end < l) return;
    if (start <= l && r <= end) {
        lazy[node] += val;
        push_down(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(node*2, l, mid, start, end, val);
    update(node*2+1, mid+1, r, start, end, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int query(int node, int l, int r, int k) {
    push_down(node, l, r);
    if (l == r) return tree[node];
    int mid = (l + r) / 2;
    push_down(node*2, l, mid);
    if (tree[node*2] >= k) return query(node*2, l, mid, k);
    else return tree[node*2] + query(node*2+1, mid+1, r, k - tree[node*2]);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &tasks[i].start, &tasks[i].end, &tasks[i].priority);
    }

    memset(priorityCounts, 0, sizeof(priorityCounts));
    for (int i = 0; i < m; i++) {
        priorityCounts[tasks[i].start].priority += tasks[i].priority;
        priorityCounts[tasks[i].start].count++;
        priorityCounts[tasks[i].end + 1].priority -= tasks[i].priority;
        priorityCounts[tasks[i].end + 1].count--;
    }

    qsort(priorityCounts + 1, n, sizeof(PriorityCount), cmp);

    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));

    for (int i = 1; i <= n; i++) {
        update(1, 1, n, 1, i, priorityCounts[i].count);
    }

    long long pre = 1;
    for (int i = 0; i < n; i++) {
        int x, a, b, c;
        scanf("%d %d %d %d", &x, &a, &b, &c);

        long long k = 1 + (a * pre + b) % c;
        int total = query(1, 1, n, n);
        if (k >= total) {
            pre = query(1, 1, n, total);
        } else {
            pre = query(1, 1, n, k);
        }
        printf("%lld\n", pre);
    }

    return 0;
}
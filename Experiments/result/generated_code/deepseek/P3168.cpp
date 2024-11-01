#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXP 10000005

typedef struct {
    int s, e, p;
} Task;

typedef struct {
    int x, a, b, c;
} Query;

Task tasks[MAXN];
Query queries[MAXN];
int n, m;

typedef struct {
    int priority;
    int count;
} Node;

Node tree[MAXP * 4];

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node].priority += val;
        tree[node].count += (val > 0) ? 1 : -1;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(node * 2, start, mid, idx, val);
        } else {
            update(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree[node].priority = tree[node * 2].priority + tree[node * 2 + 1].priority;
        tree[node].count = tree[node * 2].count + tree[node * 2 + 1].count;
    }
}

int query(int node, int start, int end, int k) {
    if (start == end) {
        return start;
    }
    int mid = (start + end) / 2;
    if (tree[node * 2].count >= k) {
        return query(node * 2, start, mid, k);
    } else {
        return query(node * 2 + 1, mid + 1, end, k - tree[node * 2].count);
    }
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &tasks[i].s, &tasks[i].e, &tasks[i].p);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &queries[i].x, &queries[i].a, &queries[i].b, &queries[i].c);
    }

    for (int i = 0; i < m; i++) {
        update(1, 1, MAXP, tasks[i].p, tasks[i].e - tasks[i].s + 1);
    }

    long long pre = 1;
    for (int i = 0; i < n; i++) {
        int x = queries[i].x;
        int a = queries[i].a;
        int b = queries[i].b;
        int c = queries[i].c;
        int k = 1 + (a * pre + b) % c;

        if (k > tree[1].count) {
            pre = tree[1].priority;
        } else {
            int idx = query(1, 1, MAXP, k);
            pre = 0;
            for (int j = 1; j <= idx; j++) {
                pre += tree[j].priority;
            }
        }
        printf("%lld\n", pre);
    }

    return 0;
}
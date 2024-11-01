#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

typedef long long ll;

struct Task {
    int start, end, priority;
};

struct Query {
    int time, a, b, c;
};

struct Task tasks[MAXM];
struct Query queries[MAXN];
int tree[MAXN * 4];
int lazy[MAXN * 4];
int m, n;

void push_down(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) >> 1;
        tree[node * 2] += lazy[node] * (mid - l + 1);
        tree[node * 2 + 1] += lazy[node] * (r - mid);
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[node] += val * (r - l + 1);
        lazy[node] += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(node * 2, l, mid, ql, qr, val);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int l, int r, int k) {
    if (l == r) return tree[node] >= k ? l : -1;
    push_down(node, l, r);
    int mid = (l + r) >> 1;
    if (tree[node * 2] >= k) return query(node * 2, l, mid, k);
    return query(node * 2 + 1, mid + 1, r, k - tree[node * 2]);
}

int cmp(const void *a, const void *b) {
    return ((struct Task *)a)->priority - ((struct Task *)b)->priority;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &tasks[i].start, &tasks[i].end, &tasks[i].priority);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &queries[i].time, &queries[i].a, &queries[i].b, &queries[i].c);
    }

    qsort(tasks, m, sizeof(struct Task), cmp);

    ll pre = 1;
    for (int i = 0; i < n; i++) {
        int x = queries[i].time;
        int k = 1 + (queries[i].a * pre + queries[i].b) % queries[i].c;

        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));

        for (int j = 0; j < m; j++) {
            if (tasks[j].start <= x && x <= tasks[j].end) {
                update(1, 1, 10000000, tasks[j].priority, tasks[j].priority, 1);
            }
        }

        int idx = query(1, 1, 10000000, k);
        ll sum = 0;
        for (int j = 0; j < m; j++) {
            if (tasks[j].start <= x && x <= tasks[j].end && tasks[j].priority <= idx) {
                sum += tasks[j].priority;
            }
        }

        printf("%lld\n", sum);
        pre = sum;
    }

    return 0;
}
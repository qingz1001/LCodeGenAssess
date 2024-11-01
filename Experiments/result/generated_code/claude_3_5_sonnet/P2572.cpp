#include <stdio.h>
#include <string.h>
#define MAXN 100005
#define MAXM 100005

int n, m;
int seq[MAXN];
int tree[MAXN * 4];
int lazy[MAXN * 4];
int maxcon[MAXN * 4];
int lcon[MAXN * 4];
int rcon[MAXN * 4];

void pushup(int node) {
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
    lcon[node] = lcon[node * 2];
    rcon[node] = rcon[node * 2 + 1];
    maxcon[node] = maxcon[node * 2] > maxcon[node * 2 + 1] ? maxcon[node * 2] : maxcon[node * 2 + 1];
    
    if (rcon[node * 2] + lcon[node * 2 + 1] > maxcon[node])
        maxcon[node] = rcon[node * 2] + lcon[node * 2 + 1];
    
    if (tree[node * 2] == (node * 2 + 1) - (node * 2) + 1)
        lcon[node] += lcon[node * 2 + 1];
    if (tree[node * 2 + 1] == (node * 2 + 2) - (node * 2 + 1) + 1)
        rcon[node] += rcon[node * 2];
}

void build(int node, int start, int end) {
    lazy[node] = -1;
    if (start == end) {
        tree[node] = seq[start];
        maxcon[node] = lcon[node] = rcon[node] = seq[start];
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    pushup(node);
}

void pushdown(int node, int start, int end) {
    if (lazy[node] != -1) {
        int mid = (start + end) / 2;
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
        tree[node * 2] = lazy[node] * (mid - start + 1);
        tree[node * 2 + 1] = lazy[node] * (end - mid);
        maxcon[node * 2] = lcon[node * 2] = rcon[node * 2] = lazy[node] ? mid - start + 1 : 0;
        maxcon[node * 2 + 1] = lcon[node * 2 + 1] = rcon[node * 2 + 1] = lazy[node] ? end - mid : 0;
        lazy[node] = -1;
    }
}

void update(int node, int start, int end, int l, int r, int val) {
    if (l <= start && end <= r) {
        lazy[node] = val;
        tree[node] = val * (end - start + 1);
        maxcon[node] = lcon[node] = rcon[node] = val ? end - start + 1 : 0;
        return;
    }
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update(node * 2, start, mid, l, r, val);
    if (r > mid) update(node * 2 + 1, mid + 1, end, l, r, val);
    pushup(node);
}

void flip(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        tree[node] = (end - start + 1) - tree[node];
        maxcon[node] = lcon[node] = rcon[node] = end - start + 1 - maxcon[node];
        if (lazy[node] != -1) lazy[node] = 1 - lazy[node];
        else lazy[node] = 1;
        return;
    }
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) flip(node * 2, start, mid, l, r);
    if (r > mid) flip(node * 2 + 1, mid + 1, end, l, r);
    pushup(node);
}

int query_sum(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) return tree[node];
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    int sum = 0;
    if (l <= mid) sum += query_sum(node * 2, start, mid, l, r);
    if (r > mid) sum += query_sum(node * 2 + 1, mid + 1, end, l, r);
    return sum;
}

int query_max(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) return maxcon[node];
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    int max_left = 0, max_right = 0, cross = 0;
    if (l <= mid) max_left = query_max(node * 2, start, mid, l, r);
    if (r > mid) max_right = query_max(node * 2 + 1, mid + 1, end, l, r);
    if (l <= mid && r > mid) {
        int left_con = rcon[node * 2] < mid - l + 1 ? rcon[node * 2] : mid - l + 1;
        int right_con = lcon[node * 2 + 1] < r - mid ? lcon[node * 2 + 1] : r - mid;
        cross = left_con + right_con;
    }
    return max_left > max_right ? (max_left > cross ? max_left : cross) : (max_right > cross ? max_right : cross);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &seq[i]);
    }
    build(1, 1, n);
    
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        l++; r++;  // 将0-based转换为1-based
        switch(op) {
            case 0:
                update(1, 1, n, l, r, 0);
                break;
            case 1:
                update(1, 1, n, l, r, 1);
                break;
            case 2:
                flip(1, 1, n, l, r);
                break;
            case 3:
                printf("%d\n", query_sum(1, 1, n, l, r));
                break;
            case 4:
                printf("%d\n", query_max(1, 1, n, l, r));
                break;
        }
    }
    return 0;
}
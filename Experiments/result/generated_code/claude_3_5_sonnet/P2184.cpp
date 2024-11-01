#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 100005

int n, m;
int tree[MAX_N * 4];
int lazy[MAX_N * 4];

void push_down(int node, int start, int end) {
    if (lazy[node] != 0) {
        int mid = (start + end) / 2;
        tree[node * 2] = lazy[node];
        tree[node * 2 + 1] = lazy[node];
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, int val) {
    if (l > end || r < start) return;
    if (l <= start && end <= r) {
        tree[node] = val;
        lazy[node] = val;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    update(node * 2, start, mid, l, r, val);
    update(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node * 2] | tree[node * 2 + 1];
}

int query(int node, int start, int end, int l, int r) {
    if (l > end || r < start) return 0;
    if (l <= start && end <= r) return tree[node];
    push_down(node, start, end);
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, l, r) | query(node * 2 + 1, mid + 1, end, l, r);
}

int count_bits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));

    int type, l, r;
    int mine_type = 1;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &type, &l, &r);
        if (type == 1) {
            update(1, 1, n, l, r, mine_type);
            mine_type = mine_type << 1;
            if (mine_type == 0) mine_type = 1;
        } else {
            int result = query(1, 1, n, l, r);
            printf("%d\n", count_bits(result));
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

int tree[MAXN * 4];
int lazy[MAXN * 4];

void push_down(int node, int l, int r) {
    if (lazy[node]) {
        int mid = (l + r) / 2;
        tree[node * 2] = tree[node * 2 + 1] = lazy[node];
        lazy[node * 2] = lazy[node * 2 + 1] = lazy[node];
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
    tree[node] = (tree[node * 2] == tree[node * 2 + 1]) ? tree[node * 2] : 0;
}

int query(int node, int start, int end, int l, int r) {
    if (l > end || r < start) return 0;
    if (l <= start && end <= r) return tree[node];
    push_down(node, start, end);
    int mid = (start + end) / 2;
    int left = query(node * 2, start, mid, l, r);
    int right = query(node * 2 + 1, mid + 1, end, l, r);
    return (left == right) ? left : 0;
}

int main() {
    int n, m, q, l, r;
    scanf("%d %d", &n, &m);

    int mine_type = 0;
    while (m--) {
        scanf("%d %d %d", &q, &l, &r);
        if (q == 1) {
            update(1, 1, n, l, r, ++mine_type);
        } else {
            int result = 0;
            int last = 0;
            for (int i = l; i <= r; i++) {
                int current = query(1, 1, n, i, i);
                if (current != last) {
                    result++;
                    last = current;
                }
            }
            printf("%d\n", result);
        }
    }

    return 0;
}
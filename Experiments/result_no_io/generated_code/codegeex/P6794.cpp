#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 400005;

struct Operation {
    int type, i, x, h;
} operations[N];

int n, q, h[N], ans[N], cnt, rt[N];

struct Node {
    int ls, rs, val;
} tree[N * 20];

void update(int &u, int l, int r, int x, int h) {
    tree[++cnt] = tree[u];
    u = cnt;
    tree[u].val++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) update(tree[u].ls, l, mid, x, h);
    else update(tree[u].rs, mid + 1, r, x, h);
}

int query(int u, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (tree[tree[u].ls].val >= k) return query(tree[u].ls, l, mid, k);
    return query(tree[u].rs, mid + 1, r, k - tree[tree[u].ls].val);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2; i < n; i++) scanf("%d", &h[i]);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d%d", &operations[i].type, &operations[i].i, &operations[i].x);
        if (operations[i].type == 0 || operations[i].type == 2) scanf("%d", &operations[i].h);
    }

    rt[0] = 1;
    for (int i = 1; i <= q; i++) {
        int op = operations[i].type, x = operations[i].x, h = operations[i].h;
        if (op == 0) {
            int k = query(rt[operations[i].i], 1, n, x);
            if (h > h[k]) update(rt[i], 1, n, k, h);
        } else if (op == 1) {
            int k = query(rt[operations[i].i], 1, n, x);
            if (k != x) update(rt[i], 1, n, k, h[k]);
        } else if (op == 2) {
            int k = query(rt[operations[i].i], 1, n, x);
            if (h < h[k]) update(rt[i], 1, n, k, h);
        } else if (op == 3) {
            int k = query(rt[operations[i].i], 1, n, x);
            ans[i] = h[k];
        }
        rt[i] = rt[operations[i].i];
    }

    for (int i = 1; i <= q; i++) if (operations[i].type == 3) printf("%d\n", ans[i]);

    return 0;
}
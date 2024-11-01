#include <stdio.h>
#include <stdlib.h>

#define MAXN 20001

int a[MAXN], sorted[MAXN], tree[MAXN][2];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int query(int l, int r, int x) {
    int ans = 0;
    for (int i = 0; i < 2; i++) {
        int p = l, q = r;
        while (p <= q) {
            int mid = (p + q) / 2;
            if (tree[mid][i] < x) {
                p = mid + 1;
            } else {
                q = mid - 1;
            }
        }
        ans += r - p + 1;
    }
    return ans;
}

int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sorted[i] = a[i];
    }
    qsort(sorted, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            int p = 0, q = i;
            while (p <= q) {
                int mid = (p + q) / 2;
                if (sorted[mid] <= a[i]) {
                    p = mid + 1;
                } else {
                    q = mid - 1;
                }
            }
            tree[i][j] = p;
        }
    }
    scanf("%d", &q);
    int last_ans = 0;
    for (int i = 0; i < q; i++) {
        int a, b, c, d, q[4];
        scanf("%d%d%d%d", &a, &b, &c, &d);
        q[0] = (a + last_ans) % n;
        q[1] = (b + last_ans) % n;
        q[2] = (c + last_ans) % n;
        q[3] = (d + last_ans) % n;
        qsort(q, 4, sizeof(int), cmp);
        a = q[0], b = q[1], c = q[2], d = q[3];
        int l = 1, r = 1000000000, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (query(a, b, mid) >= (b - a + 1) / 2 + 1 && query(c, d, mid) >= (d - c + 1) / 2 + 1) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        printf("%d\n", ans);
        last_ans = ans;
    }
    return 0;
}
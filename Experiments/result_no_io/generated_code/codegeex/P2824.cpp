#include <stdio.h>
#include <string.h>

int n, m, a[100005], q, op, l, r, b[100005], cnt, c[100005];

void merge(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1, i = l, j = mid + 1, k = l;
    merge(l, mid);
    merge(mid + 1, r);
    while (i <= mid && j <= r) {
        if (b[i] < b[j]) c[k++] = b[i++];
        else c[k++] = b[j++];
    }
    while (i <= mid) c[k++] = b[i++];
    while (j <= r) c[k++] = b[j++];
    for (int i = l; i <= r; i++) b[i] = c[i];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 0) {
            for (int j = l; j <= r; j++) b[++cnt] = a[j];
            merge(1, cnt);
            for (int j = l; j <= r; j++) a[j] = b[j - l + 1];
            cnt = 0;
        } else {
            for (int j = l; j <= r; j++) b[++cnt] = a[j];
            merge(1, cnt);
            for (int j = l; j <= r; j++) a[j] = b[r - j + l + 1];
            cnt = 0;
        }
    }
    scanf("%d", &q);
    printf("%d\n", a[q]);
    return 0;
}
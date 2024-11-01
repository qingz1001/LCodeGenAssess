#include <stdio.h>

int n, m, a[100005], q;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) {
            // 升序排序
            while (l < r) {
                if (a[l] > a[r]) {
                    int t = a[l];
                    a[l] = a[r];
                    a[r] = t;
                }
                l++;
                r--;
            }
        } else {
            // 降序排序
            while (l < r) {
                if (a[l] < a[r]) {
                    int t = a[l];
                    a[l] = a[r];
                    a[r] = t;
                }
                l++;
                r--;
            }
        }
    }
    scanf("%d", &q);
    printf("%d\n", a[q]);
    return 0;
}
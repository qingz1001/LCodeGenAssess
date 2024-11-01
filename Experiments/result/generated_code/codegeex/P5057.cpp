#include <stdio.h>

int n, m;
int a[100005];

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        int t, l, r;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &l, &r);
            for (int i = l; i <= r; i++) {
                a[i] = !a[i];
            }
        } else if (t == 2) {
            scanf("%d", &l);
            printf("%d\n", a[l]);
        }
    }
    return 0;
}
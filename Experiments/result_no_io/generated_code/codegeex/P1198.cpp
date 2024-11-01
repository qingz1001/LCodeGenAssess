#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

int m, d;
char op[2];
int n, l;
int a[MAXN];
int t;

int main() {
    scanf("%d%d", &m, &d);
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            scanf("%d", &l);
            int max = a[m - l];
            for (int i = m - l + 1; i < m; i++) {
                if (a[i] > max) {
                    max = a[i];
                }
            }
            t = max;
            printf("%d\n", t);
        } else if (op[0] == 'A') {
            scanf("%d", &n);
            n = (n + t) % d;
            a[m] = n;
        }
    }
    return 0;
}
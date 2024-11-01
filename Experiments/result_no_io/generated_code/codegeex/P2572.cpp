#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int n, m;
int a[MAXN];
int op[MAXM], l[MAXM], r[MAXM];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &op[i], &l[i], &r[i]);
    }
    
    for (int i = 1; i <= m; i++) {
        if (op[i] == 0) {
            // 把 [l, r] 区间内的所有数全变成 0
            for (int j = l[i]; j <= r[i]; j++) {
                a[j] = 0;
            }
        } else if (op[i] == 1) {
            // 把 [l, r] 区间内的所有数全变成 1
            for (int j = l[i]; j <= r[i]; j++) {
                a[j] = 1;
            }
        } else if (op[i] == 2) {
            // 把 [l, r] 区间内的所有数全部取反
            for (int j = l[i]; j <= r[i]; j++) {
                a[j] = 1 - a[j];
            }
        } else if (op[i] == 3) {
            // 询问 [l, r] 区间内总共有多少个 1
            int count = 0;
            for (int j = l[i]; j <= r[i]; j++) {
                count += a[j];
            }
            printf("%d\n", count);
        } else if (op[i] == 4) {
            // 询问 [l, r] 区间内最多有多少个连续的 1
            int maxConsecutive = 0, currentConsecutive = 0;
            for (int j = l[i]; j <= r[i]; j++) {
                if (a[j] == 1) {
                    currentConsecutive++;
                    maxConsecutive = (currentConsecutive > maxConsecutive) ? currentConsecutive : maxConsecutive;
                } else {
                    currentConsecutive = 0;
                }
            }
            printf("%d\n", maxConsecutive);
        }
    }
    
    return 0;
}
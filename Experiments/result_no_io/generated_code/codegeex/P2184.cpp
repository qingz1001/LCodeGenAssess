#include <stdio.h>
#include <string.h>

#define MAXN 100005

int n, m;
int q, l, r;
int a[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d%d", &q, &l, &r);
        if (q == 1) {
            // SCV 在 [l, r] 区间布上一种地雷
            for (int i = l; i <= r; i++) {
                a[i]++;
            }
        } else if (q == 2) {
            // 小 FF 询问当前 [l, r] 区间总共有多少种地雷
            int sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            printf("%d\n", sum);
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 53280
#define MAXM 150960

int n, m, x;
int u[MAXM], v[MAXM], w[MAXM];
int cnt = 0;

int main() {
    // 读取输入
    scanf("%*d%d%d%d", &n, &m, &x);
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
    }

    // 初始化操作方案
    for (int i = 0; i < m; i++) {
        if ((w[i] | x) < x) {
            cnt++;
            x = w[i] | x;
        }
    }

    // 输出操作方案
    printf("%d\n", cnt);
    for (int i = 0; i < m; i++) {
        if ((w[i] | x) < x) {
            printf("%d %d %d\n", u[i], v[i], w[i]);
        }
    }

    return 0;
}
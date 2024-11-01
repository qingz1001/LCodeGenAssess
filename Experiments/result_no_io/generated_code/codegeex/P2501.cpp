#include <stdio.h>
#include <stdlib.h>

#define MAXN 35005
#define INF 0x3f3f3f3f

int a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int n, m, f[MAXN], ans = INF;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    // 对数组进行排序
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (b[i] > b[j]) {
                int temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }

    // 处理第一问
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) {
            cnt++;
        }
    }
    printf("%d\n", cnt);

    // 处理第二问
    for (int i = 1; i <= n; i++) {
        int k = lower_bound(b + 1, b + n + 1, a[i]) - b;
        int t = 0;
        for (int j = 1; j <= k; j++) {
            t += abs(a[i] - b[j]);
        }
        for (int j = k; j <= n; j++) {
            t -= abs(a[i] - b[j]);
        }
        ans = min(ans, t);
    }
    printf("%d\n", ans);

    return 0;
}
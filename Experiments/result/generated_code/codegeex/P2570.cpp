#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 31
#define MAX 100000000

int n, m;
int p[N], r[N], d[N], s[N];
int T;

int left[N], right[N];
int cnt[N * 2];
int f[N][N * 2];

void init() {
    int i;
    for (i = 1; i <= n; i++) {
        left[i] = 0;
        right[i] = MAX;
    }
    memset(cnt, 0, sizeof(cnt));
    memset(f, 0, sizeof(f));
}

double check(double T) {
    int i, j, k;
    double t;
    init();
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            t = (double)p[i] / s[j];
            if (t < right[i] - left[i]) {
                f[j][left[i] + (int)t] = 1;
            }
        }
        for (j = 1; j <= N * 2; j++) {
            for (k = 1; k <= j; k++) {
                f[j] |= f[j - k][k];
            }
        }
        for (j = 1; j <= N * 2; j++) {
            if (f[j][j]) {
                left[i] = j;
            }
        }
        for (j = N * 2 - 1; j >= 1; j--) {
            if (f[j][j]) {
                right[i] = j;
            }
        }
        for (j = left[i]; j <= right[i]; j++) {
            cnt[j]++;
        }
    }
    for (j = 1; j <= N * 2; j++) {
        if (cnt[j] >= m) {
            return j - 1;
        }
    }
    return -1;
}

int main() {
    int K, i;
    scanf("%d", &K);
    while (K--) {
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; i++) {
            scanf("%d%d%d", &p[i], &r[i], &d[i]);
            d[i] += T;
        }
        for (i = 1; i <= m; i++) {
            scanf("%d", &s[i]);
        }
        printf("%.4lf\n", check(0.0));
    }
    return 0;
}
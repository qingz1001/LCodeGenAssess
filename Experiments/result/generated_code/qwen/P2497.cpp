#include <stdio.h>
#include <math.h>

#define EPS 1e-9

typedef struct {
    double x, r, v;
} Base;

int compare(const void *a, const void *b) {
    return (*(Base *)a).x < (*(Base *)b).x ? -1 : 1;
}

double solve(double x[], double r[], double v[], int n, int m) {
    Base bases[n];
    for (int i = 0; i < n; i++) {
        bases[i].x = x[i];
        bases[i].r = r[i];
        bases[i].v = v[i];
    }
    qsort(bases, n, sizeof(Base), compare);

    double dp[n][m + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 1e18;
        }
    }

    dp[0][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i - 1][j] < 1e18) {
                dp[i][j] = fmin(dp[i][j], dp[i - 1][j] + bases[i].v);
            }
            for (int k = 0; k <= j && k <= i - 1; k++) {
                double dist = bases[i].x - bases[k].x;
                if (dist >= bases[k].r + bases[i].r) {
                    double cost = sqrt(bases[i].v) + bases[k].v;
                    dp[i][j] = fmin(dp[i][j], dp[k][j - k] + cost);
                }
            }
        }
    }

    double ans = 1e18;
    for (int j = 0; j <= m; j++) {
        ans = fmin(ans, dp[n - 1][j]);
    }

    return ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    double x[n], r[n], v[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &x[i], &r[i], &v[i]);
    }

    printf("%.3f\n", solve(x, r, v, n, m));
    return 0;
}
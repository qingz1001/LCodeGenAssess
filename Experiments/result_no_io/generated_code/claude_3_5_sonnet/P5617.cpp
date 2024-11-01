#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define MAX_N 100005

int n, k, r;
int x[MAX_N];
double dp[MAX_N];

double calc(int i, int j) {
    if (x[j] - x[i] >= 2 * r) {
        return 2 * PI * r * r;
    }
    double d = x[j] - x[i];
    double theta = 2 * acos(d / (2 * r));
    double area = r * r * (theta - sin(theta));
    return 2 * PI * r * r - 2 * area;
}

int main() {
    scanf("%d %d %d", &n, &k, &r);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    for (int i = 0; i < n; i++) {
        dp[i] = PI * r * r;
        for (int j = 0; j < i; j++) {
            double area = calc(j, i);
            if (j > 0) {
                area += dp[j-1];
            }
            if (area > dp[i]) {
                dp[i] = area;
            }
        }
    }

    double ans = 0;
    for (int i = k-1; i < n; i++) {
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }

    printf("%.10f\n", ans);

    return 0;
}
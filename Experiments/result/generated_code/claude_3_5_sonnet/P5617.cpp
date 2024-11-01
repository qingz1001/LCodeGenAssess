#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005
#define PI 3.14159265358979323846

int n, k;
double r;
int x[MAX_N];
double dp[MAX_N];

double get_area(int i, int j) {
    if (x[j] - x[i] >= 2 * r) return 2 * PI * r * r;
    double d = x[j] - x[i];
    double theta = 2 * acos(d / (2 * r));
    double area = r * r * (theta - sin(theta));
    return 2 * PI * r * r - 2 * area;
}

int main() {
    scanf("%d %d %lf", &n, &k, &r);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    for (int i = 0; i < n; i++) {
        dp[i] = get_area(i, i);
        for (int j = 0; j < i; j++) {
            if (i - j > k) continue;
            double area = dp[j] + get_area(j + 1, i);
            if (area > dp[i]) dp[i] = area;
        }
    }

    double ans = 0;
    for (int i = n - k; i < n; i++) {
        if (dp[i] > ans) ans = dp[i];
    }

    printf("%.8f\n", ans);
    return 0;
}
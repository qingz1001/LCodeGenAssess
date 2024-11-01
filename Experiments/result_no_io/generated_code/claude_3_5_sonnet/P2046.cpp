#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 501
#define INF 1e18

int n;
long long flow[MAXN][MAXN][4];
double height[MAXN][MAXN];

void read_input() {
    scanf("%d", &n);
    for (int d = 0; d < 4; d++) {
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < n + (d % 2); j++) {
                scanf("%lld", &flow[i][j][d]);
            }
        }
    }
}

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

void solve() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            height[i][j] = INF;
        }
    }
    height[0][0] = 0;
    height[n][n] = 1;

    double left = 0, right = 1;
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        height[n][0] = mid;

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if ((i == 0 && j == 0) || (i == n && j == 0) || (i == n && j == n)) continue;
                height[i][j] = INF;
                if (i > 0) height[i][j] = min(height[i][j], height[i-1][j]);
                if (j > 0) height[i][j] = min(height[i][j], height[i][j-1]);
                if (i < n) height[i][j] = min(height[i][j], height[i+1][j]);
                if (j < n) height[i][j] = min(height[i][j], height[i][j+1]);
            }
        }

        int flag = 1;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i < n && height[i+1][j] - height[i][j] > 1) flag = 0;
                if (j < n && height[i][j+1] - height[i][j] > 1) flag = 0;
            }
        }

        if (flag) right = mid;
        else left = mid;
    }

    double ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            ans += flow[i][j][0] * max(0, height[i][j+1] - height[i][j]);
            ans += flow[i][j][2] * max(0, height[i][j] - height[i][j+1]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            ans += flow[i][j][1] * max(0, height[i+1][j] - height[i][j]);
            ans += flow[i][j][3] * max(0, height[i][j] - height[i+1][j]);
        }
    }

    printf("%.0f\n", round(ans));
}

int main() {
    read_input();
    solve();
    return 0;
}
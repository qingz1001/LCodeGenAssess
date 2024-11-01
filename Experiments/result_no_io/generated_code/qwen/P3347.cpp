#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define INF 1e9

int n, m;
double a[MAXN], b[MAXN], c[MAXN];
int d[MAXN];
int adj[MAXN][MAXN];

double min(double x, double y) {
    return x < y ? x : y;
}

double max(double x, double y) {
    return x > y ? x : y;
}

void floyd() {
    for (int k = 1; k <= n + m; k++) {
        for (int i = 1; i <= n + m; i++) {
            for (int j = 1; j <= n + m; j++) {
                if (adj[i][k] && adj[k][j]) {
                    adj[i][j] = 1;
                }
            }
        }
    }
}

double cost(int i, int j, double x) {
    if (i <= n && j > n) {
        return a[i - 1] * x * x + b[i - 1] * x;
    } else if (i > n && j <= n) {
        return 0;
    } else {
        return adj[i - n][j - n] ? INF : 0;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf %lf", &a[i - 1], &b[i - 1], &c[i - 1]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &d[i - 1]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    floyd();

    double total_volume = 0;
    double total_cost = 0;

    for (int i = 1; i <= n; i++) {
        double volume = 0;
        for (int j = 1; j <= m; j++) {
            if (adj[i][j]) {
                double v = min(c[i - 1], d[j - 1] - volume);
                volume += v;
                total_volume += v;
                total_cost += cost(i, j, v);
            }
        }
    }

    printf("%.0f\n", total_volume);
    printf("%.0f/%.0f\n", total_cost, 1);

    return 0;
}
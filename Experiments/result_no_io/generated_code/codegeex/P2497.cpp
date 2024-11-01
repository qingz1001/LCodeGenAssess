#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 500005

typedef struct {
    long double x, r, v;
} Node;

Node nodes[MAXN];
int n, m;
long double dp[MAXN];

inline long double min(long double a, long double b) {
    return a < b ? a : b;
}

inline long double calc(int i, int j) {
    return nodes[j].r + sqrt(nodes[i].r) + dp[j];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%Lf %Lf %Lf", &nodes[i].x, &nodes[i].r, &nodes[i].v);
    }

    dp[1] = nodes[1].v;
    for (int i = 2; i <= n; i++) {
        dp[i] = nodes[i].v;
        for (int j = 1; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + calc(i, j));
        }
    }

    printf("%.3Lf\n", dp[n]);
    return 0;
}
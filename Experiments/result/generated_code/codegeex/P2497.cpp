#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 500001

typedef struct {
    long long x, r, v;
} Station;

Station stations[MAXN];
long long dp[MAXN];
int n;

double calculate_distance(int i, int j) {
    return sqrt((stations[i].x - stations[j].x) * (stations[i].x - stations[j].x) + stations[i].r * stations[i].r);
}

int compare(const void *a, const void *b) {
    return (*(Station*)a).x - (*(Station*)b).x;
}

int main() {
    long long m;
    scanf("%d %lld", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &stations[i].x, &stations[i].r, &stations[i].v);
    }
    
    qsort(stations, n, sizeof(Station), compare);
    
    for (int i = 0; i < n; i++) {
        dp[i] = stations[i].v;
        for (int j = 0; j < i; j++) {
            if (stations[j].x + stations[j].r >= stations[i].x) {
                double distance = calculate_distance(i, j);
                if (distance - stations[i].r <= 1e-6) {
                    dp[i] = fmin(dp[i], dp[j] + stations[i].r);
                }
            }
        }
    }
    
    double min_cost = dp[0];
    for (int i = 1; i < n; i++) {
        if (stations[i].x + stations[i].r >= m) {
            double distance = calculate_distance(i, n-1);
            if (distance - stations[n-1].r <= 1e-6) {
                min_cost = fmin(min_cost, dp[i] + stations[n-1].r);
            }
        }
    }
    
    printf("%.3lf\n", min_cost);
    return 0;
}
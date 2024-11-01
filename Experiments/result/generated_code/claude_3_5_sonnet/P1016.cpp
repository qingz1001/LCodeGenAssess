#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STATIONS 8  // 包括起点和终点
#define INF 1e9

typedef struct {
    double distance;
    double price;
} Station;

int compare(const void* a, const void* b) {
    return ((Station*)a)->distance - ((Station*)b)->distance;
}

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    double D1, C, D2, P;
    int N;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);

    Station stations[MAX_STATIONS];
    stations[0] = (Station){0, P};
    for (int i = 1; i <= N; i++) {
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }
    stations[N+1] = (Station){D1, 0};
    N += 2;

    qsort(stations, N, sizeof(Station), compare);

    double dp[MAX_STATIONS] = {0};
    for (int i = 1; i < N; i++) {
        double dist = stations[i].distance - stations[i-1].distance;
        if (dist > C * D2) {
            printf("No Solution\n");
            return 0;
        }
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            if (stations[i].distance - stations[j].distance > C * D2) break;
            double need = (stations[i].distance - stations[j].distance) / D2;
            dp[i] = min(dp[i], dp[j] + need * stations[j].price);
        }
    }

    printf("%.2f\n", round(dp[N-1] * 100) / 100);
    return 0;
}
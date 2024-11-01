#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2800
#define MAX_Q 3000000
#define MAX_T 1000000000

typedef struct {
    int T;
    int A;
    int B;
    int C;
} Customer;

typedef struct {
    int P;
    int X;
} Plan;

int compare(const void *a, const void *b) {
    return ((Customer *)a)->T - ((Customer *)b)->T;
}

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    Customer customers[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &customers[i].T, &customers[i].A, &customers[i].B, &customers[i].C);
    }

    Plan plans[MAX_Q];
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &plans[i].P, &plans[i].X);
    }

    qsort(customers, N, sizeof(Customer), compare);

    double dp[MAX_N + 1][MAX_T + 1];
    for (int i = 0; i <= N; i++) {
        for (int t = 0; t <= MAX_T; t++) {
            dp[i][t] = -1e18;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int t = 0; t <= MAX_T; t++) {
            if (dp[i][t] == -1e18) continue;

            int dt = abs(customers[i].B - customers[i].A);
            double cost = customers[i].C * dt / 2.0;

            dp[i + 1][max(t, customers[i].T)] = max(dp[i + 1][max(t, customers[i].T)], dp[i][t]);
            dp[i + 1][min(t + dt, customers[i].T + dt)] = max(dp[i + 1][min(t + dt, customers[i].T + dt)], dp[i][t] + cost);
        }
    }

    for (int j = 0; j < Q; j++) {
        printf("%.0f\n", dp[N][plans[j].P]);
    }

    return 0;
}
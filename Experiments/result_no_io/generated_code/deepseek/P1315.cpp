#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 10005
#define MAXK 100005

int n, m, k;
int D[MAXN];
int T[MAXM], A[MAXM], B[MAXM];
int arrival[MAXN], departure[MAXN];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i < n; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &T[i], &A[i], &B[i]);
    }

    // Initialize arrival and departure times
    for (int i = 1; i <= n; i++) {
        arrival[i] = 0;
        departure[i] = 0;
    }

    // Calculate initial arrival and departure times
    for (int i = 1; i <= m; i++) {
        departure[A[i]] = (departure[A[i]] > T[i]) ? departure[A[i]] : T[i];
    }

    for (int i = 2; i <= n; i++) {
        arrival[i] = departure[i - 1] + D[i - 1];
        departure[i] = arrival[i];
        for (int j = 1; j <= m; j++) {
            if (A[j] == i - 1 && B[j] >= i) {
                departure[i] = (departure[i] > T[j]) ? departure[i] : T[j];
            }
        }
    }

    // Calculate initial total travel time
    int total_time = 0;
    for (int i = 1; i <= m; i++) {
        total_time += arrival[B[i]] - T[i];
    }

    // Use accelerators to minimize total travel time
    while (k > 0) {
        int max_reduction = 0;
        int best_index = 0;

        for (int i = 1; i < n; i++) {
            if (D[i] == 0) continue;

            int reduction = 0;
            for (int j = 1; j <= m; j++) {
                if (A[j] == i && B[j] > i) {
                    reduction += (arrival[B[j]] - T[j]);
                }
            }

            if (reduction > max_reduction) {
                max_reduction = reduction;
                best_index = i;
            }
        }

        if (max_reduction == 0) break;

        D[best_index]--;
        k--;

        // Update arrival and departure times
        for (int i = best_index + 1; i <= n; i++) {
            arrival[i] = departure[i - 1] + D[i - 1];
            departure[i] = arrival[i];
            for (int j = 1; j <= m; j++) {
                if (A[j] == i - 1 && B[j] >= i) {
                    departure[i] = (departure[i] > T[j]) ? departure[i] : T[j];
                }
            }
        }

        // Recalculate total travel time
        total_time = 0;
        for (int i = 1; i <= m; i++) {
            total_time += arrival[B[i]] - T[i];
        }
    }

    printf("%d\n", total_time);
    return 0;
}
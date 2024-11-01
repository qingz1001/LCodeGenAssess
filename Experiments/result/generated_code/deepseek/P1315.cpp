#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 10005
#define MAXK 100005

int n, m, k;
int D[MAXN];
int T[MAXM], A[MAXM], B[MAXM];
int arrival[MAXN], departure[MAXN];
int benefit[MAXN];

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
        arrival[i] = departure[i] = 0;
    }

    // Calculate initial arrival and departure times
    for (int i = 1; i <= m; i++) {
        departure[A[i]] = (departure[A[i]] > T[i]) ? departure[A[i]] : T[i];
    }
    for (int i = 2; i <= n; i++) {
        arrival[i] = departure[i - 1] + D[i - 1];
        departure[i] = arrival[i];
    }
    for (int i = 1; i <= m; i++) {
        arrival[B[i]] = (arrival[B[i]] > departure[A[i]] + (B[i] - A[i]) * D[A[i]]) ? arrival[B[i]] : departure[A[i]] + (B[i] - A[i]) * D[A[i]];
    }

    // Calculate initial total travel time
    int total_time = 0;
    for (int i = 1; i <= m; i++) {
        total_time += arrival[B[i]] - T[i];
    }

    // Use accelerators
    while (k > 0) {
        // Calculate benefit of reducing each D[i]
        for (int i = 1; i < n; i++) {
            benefit[i] = 0;
            if (D[i] > 0) {
                for (int j = 1; j <= m; j++) {
                    if (A[j] <= i && B[j] > i) {
                        benefit[i] += (arrival[i + 1] - departure[i]) - (arrival[i + 1] - (departure[i] + D[i] - 1));
                    }
                }
            }
        }

        // Find the best D[i] to reduce
        int best_benefit = 0, best_index = 0;
        for (int i = 1; i < n; i++) {
            if (benefit[i] > best_benefit) {
                best_benefit = benefit[i];
                best_index = i;
            }
        }

        // If no benefit, break
        if (best_benefit == 0) break;

        // Reduce D[best_index]
        D[best_index]--;
        k--;

        // Update arrival and departure times
        for (int i = best_index + 1; i <= n; i++) {
            arrival[i] = departure[i - 1] + D[i - 1];
            departure[i] = arrival[i];
        }
        for (int i = 1; i <= m; i++) {
            arrival[B[i]] = (arrival[B[i]] > departure[A[i]] + (B[i] - A[i]) * D[A[i]]) ? arrival[B[i]] : departure[A[i]] + (B[i] - A[i]) * D[A[i]];
        }

        // Update total travel time
        total_time -= best_benefit;
    }

    printf("%d\n", total_time);
    return 0;
}
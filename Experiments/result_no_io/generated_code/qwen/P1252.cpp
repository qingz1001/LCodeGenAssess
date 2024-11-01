#include <stdio.h>
#include <stdlib.h>

#define N 5
#define MAX_KM 10

int main() {
    int times[N][MAX_KM + 1];
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= MAX_KM; ++j) {
            scanf("%d", &times[i][j]);
        }
    }

    int min_time = INT_MAX;
    int best_km[N];

    // Try all possible distributions of distances
    for (int a = 1; a <= 10; ++a) {
        for (int b = 1; b <= 10 - a; ++b) {
            for (int c = 1; c <= 10 - a - b; ++c) {
                for (int d = 1; d <= 10 - a - b - c; ++d) {
                    int e = 10 - a - b - c - d;
                    if (e > 0 && e <= 10) {
                        int total_time = times[0][a] + times[1][b] + times[2][c] + times[3][d] + times[4][e];
                        if (total_time < min_time) {
                            min_time = total_time;
                            best_km[0] = a;
                            best_km[1] = b;
                            best_km[2] = c;
                            best_km[3] = d;
                            best_km[4] = e;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", min_time);
    for (int i = 0; i < N; ++i) {
        printf("%d ", best_km[i]);
    }
    printf("\n");

    return 0;
}
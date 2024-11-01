#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 5005

int n, m;
int F[MAXN];
int T[MAXM][2];
double dist[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &F[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &T[i][0], &T[i][1], &dist[T[i][0]]);
    }

    double max_avg = 0.0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j && dist[j] > 0) {
                double avg = (F[i] + F[j]) / (dist[i] + dist[j]);
                if (avg > max_avg) {
                    max_avg = avg;
                }
            }
        }
    }

    printf("%.2f\n", max_avg);
    return 0;
}
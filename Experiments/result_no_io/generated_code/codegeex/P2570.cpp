#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 31
#define MAXM 31
#define MAXT 10000001

typedef struct {
    int p, r, d;
} Cheese;

typedef struct {
    int s;
} Mouse;

int cmp(const void *a, const void *b) {
    Cheese *ca = (Cheese *)a;
    Cheese *cb = (Cheese *)b;
    if (ca->r != cb->r) return ca->r - cb->r;
    return ca->d - cb->d;
}

int main() {
    int K;
    scanf("%d", &K);
    while (K--) {
        int n, m;
        scanf("%d%d", &n, &m);
        Cheese cheeses[MAXN];
        Mouse mice[MAXM];
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &cheeses[i].p, &cheeses[i].r, &cheeses[i].d);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &mice[i].s);
        }
        qsort(cheeses, n, sizeof(Cheese), cmp);

        double T = 0.0;
        for (int i = 0; i < n; i++) {
            double min_time = cheeses[i].d * 1.0 / mice[0].s;
            for (int j = 0; j < m; j++) {
                double time = cheeses[i].p * 1.0 / mice[j].s;
                if (cheeses[i].r + time <= cheeses[i].d) {
                    min_time = fmin(min_time, time);
                    break;
                }
            }
            T = fmax(T, min_time);
        }
        printf("%.4lf\n", T);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30
#define MAX_M 30
#define EPS 1e-9

typedef struct {
    int p, r, d;
} Cheese;

typedef struct {
    int s;
} Mouse;

int n, m, K;
Cheese cheeses[MAX_N];
Mouse mice[MAX_M];

double can_eat_all(int T) {
    for (int i = 0; i < n; i++) {
        if (cheeses[i].d + T <= cheeses[i].r || cheeses[i].d - T >= cheeses[i].r + cheeses[i].p / mice[0].s) {
            return 0;
        }
    }
    return 1;
}

double find_min_T() {
    double low = 0, high = 1e7;
    while (high - low > EPS) {
        double mid = (low + high) / 2;
        if (can_eat_all(mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return low;
}

int main() {
    scanf("%d", &K);
    while (K--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &cheeses[i].p, &cheeses[i].r, &cheeses[i].d);
        }
        for (int j = 0; j < m; j++) {
            scanf("%d", &mice[j].s);
        }
        printf("%.4f\n", find_min_T());
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 30
#define MAX_M 30
#define MAX_K 5
#define EPS 1e-5

typedef struct {
    int p, r, d;
} Cheese;

typedef struct {
    int s;
} Mouse;

int n, m;
Cheese cheeses[MAX_N];
Mouse mice[MAX_M];

int compare_cheese(const void *a, const void *b) {
    Cheese *ca = (Cheese *)a;
    Cheese *cb = (Cheese *)b;
    return ca->r - cb->r;
}

int can_eat_all(double T) {
    double time_left[MAX_N];
    for (int i = 0; i < n; i++) {
        time_left[i] = cheeses[i].d + T - cheeses[i].r;
    }

    for (int i = 0; i < m; i++) {
        double current_time = 0.0;
        for (int j = 0; j < n; j++) {
            if (time_left[j] < 0) continue;
            double eat_time = (double)cheeses[j].p / mice[i].s;
            if (current_time + eat_time <= time_left[j]) {
                current_time += eat_time;
                time_left[j] = -1; // Mark as eaten
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (time_left[i] >= 0) return 0;
    }
    return 1;
}

double binary_search(double left, double right) {
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (can_eat_all(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return (left + right) / 2;
}

int main() {
    int K;
    scanf("%d", &K);
    while (K--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &cheeses[i].p, &cheeses[i].r, &cheeses[i].d);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &mice[i].s);
        }

        qsort(cheeses, n, sizeof(Cheese), compare_cheese);

        double result = binary_search(0, 1e7);
        printf("%.4f\n", result);
    }
    return 0;
}
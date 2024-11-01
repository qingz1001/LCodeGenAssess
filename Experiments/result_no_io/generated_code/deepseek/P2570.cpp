#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 30
#define MAX_M 30
#define MAX_K 5
#define INF 1e9

typedef struct {
    int p, r, d;
} Cheese;

typedef struct {
    int s;
} Mouse;

int n, m;
Cheese cheeses[MAX_N];
Mouse mice[MAX_M];

int compareCheese(const void *a, const void *b) {
    return ((Cheese *)a)->r - ((Cheese *)b)->r;
}

int compareMouse(const void *a, const void *b) {
    return ((Mouse *)a)->s - ((Mouse *)b)->s;
}

int canEatAll(double T) {
    double time[MAX_M] = {0};
    int cheeseIndex = 0;

    for (int i = 0; i < m; i++) {
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        double minTime = INF;
        int minIndex = -1;

        for (int j = 0; j < m; j++) {
            double eatTime = (double)cheeses[i].p / mice[j].s;
            if (time[j] + eatTime < minTime) {
                minTime = time[j] + eatTime;
                minIndex = j;
            }
        }

        if (minTime > cheeses[i].d + T) {
            return 0;
        }

        time[minIndex] += minTime;
    }

    return 1;
}

double binarySearch(double left, double right) {
    double mid;
    while (right - left > 1e-5) {
        mid = (left + right) / 2;
        if (canEatAll(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
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

        qsort(cheeses, n, sizeof(Cheese), compareCheese);
        qsort(mice, m, sizeof(Mouse), compareMouse);

        double result = binarySearch(0, INF);
        printf("%.4f\n", result);
    }

    return 0;
}
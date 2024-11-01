#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-4

typedef struct {
    int pi, ri, di;
} Cheese;

typedef struct {
    int sj;
} Rat;

int compare(const void *a, const void *b) {
    return ((Cheese *)a)->ri - ((Cheese *)b)->ri;
}

double find_min_T(int n, int m, Cheese cheeses[], Rat rats[]) {
    qsort(cheeses, n, sizeof(Cheese), compare);

    double left = 0, right = 1e9;
    while (right - left > EPSILON) {
        double mid = (left + right) / 2;
        int available_rats = m;
        for (int i = 0; i < n; ++i) {
            if (cheeses[i].ri + mid >= cheeses[i].di) {
                double time_needed = (cheeses[i].pi + mid - cheeses[i].ri) / (double)rats[available_rats - 1].sj;
                if (time_needed > mid) {
                    left = mid;
                    break;
                }
                --available_rats;
                if (available_rats == 0) {
                    left = mid;
                    break;
                }
            }
        }
        if (available_rats == 0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

int main() {
    int K;
    scanf("%d", &K);
    for (int k = 0; k < K; ++k) {
        int n, m;
        scanf("%d %d", &n, &m);
        Cheese cheeses[n];
        Rat rats[m];
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d", &cheeses[i].pi, &cheeses[i].ri, &cheeses[i].di);
        }
        for (int j = 0; j < m; ++j) {
            scanf("%d", &rats[j].sj);
        }
        printf("%.4f\n", find_min_T(n, m, cheeses, rats));
    }
    return 0;
}
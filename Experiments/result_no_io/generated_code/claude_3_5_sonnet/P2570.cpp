#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 30
#define MAX_M 30
#define EPS 1e-9

typedef struct {
    int p, r, d;
} Cheese;

int n, m;
Cheese cheese[MAX_N];
int mouse[MAX_M];

int cmp(const void *a, const void *b) {
    return ((Cheese*)a)->d - ((Cheese*)b)->d;
}

int check(double T) {
    double time[MAX_M] = {0};
    int idx = 0;
    
    for (int i = 0; i < n; i++) {
        double start = fmax(cheese[i].r, time[idx]);
        double end = cheese[i].d + T;
        
        if (start + (double)cheese[i].p / mouse[idx] > end) {
            return 0;
        }
        
        time[idx] = start + (double)cheese[i].p / mouse[idx];
        idx = (idx + 1) % m;
    }
    
    return 1;
}

double solve() {
    qsort(cheese, n, sizeof(Cheese), cmp);
    
    double left = 0, right = 1e8;
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (check(mid)) {
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
            scanf("%d %d %d", &cheese[i].p, &cheese[i].r, &cheese[i].d);
        }
        
        for (int i = 0; i < m; i++) {
            scanf("%d", &mouse[i]);
        }
        
        printf("%.4f\n", solve());
    }
    
    return 0;
}
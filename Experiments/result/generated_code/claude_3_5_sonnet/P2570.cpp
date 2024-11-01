#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 30
#define MAXM 30
#define INF 1e18

typedef struct {
    int p, r, d;
} Cheese;

typedef struct {
    int s;
} Mouse;

Cheese cheese[MAXN];
Mouse mouse[MAXM];
int n, m;

int cmp(const void *a, const void *b) {
    return ((Cheese*)a)->d - ((Cheese*)b)->d;
}

int check(double T) {
    double time[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        double earliest = cheese[i].r;
        double latest = cheese[i].d + T;
        double need = cheese[i].p;
        
        for (int j = 0; j < m && need > 0; j++) {
            if (time[j] < earliest) time[j] = earliest;
            if (time[j] >= latest) continue;
            
            double can_eat = (latest - time[j]) * mouse[j].s;
            if (can_eat >= need) {
                time[j] += need / mouse[j].s;
                need = 0;
            } else {
                need -= can_eat;
                time[j] = latest;
            }
        }
        
        if (need > 0) return 0;
    }
    return 1;
}

double solve() {
    qsort(cheese, n, sizeof(Cheese), cmp);
    
    double l = 0, r = 1e8;
    while (r - l > 1e-5) {
        double mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    return l;
}

int main() {
    int K;
    scanf("%d", &K);
    while (K--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d %d %d", &cheese[i].p, &cheese[i].r, &cheese[i].d);
        for (int i = 0; i < m; i++)
            scanf("%d", &mouse[i].s);
        
        printf("%.4f\n", solve());
    }
    return 0;
}
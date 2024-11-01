#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double p;
    double r;
    double d;
} Cheese;

typedef struct {
    double s;
} Mouse;

// Comparator for sorting cheeses by d + T
int compare(const void *a, const void *b, void *T_ptr) {
    double T = *(double*)T_ptr;
    Cheese *ca = (Cheese*)a;
    Cheese *cb = (Cheese*)b;
    double da = ca->d + T;
    double db = cb->d + T;
    if (da < db) return -1;
    else if (da > db) return 1;
    else return 0;
}

int feasible(int n, int m, Cheese cheeses[], Mouse mice[], double T) {
    // Create a sorted copy of cheeses
    Cheese sorted[n];
    for(int i=0;i<n;i++) sorted[i] = cheeses[i];
    // Sort sorted by d + T
    qsort_r(sorted, n, sizeof(Cheese), compare, &T);
    // Initialize mouse finish times
    double finish[m];
    for(int i=0;i<m;i++) finish[i] = 0.0;
    // Assign each cheese
    for(int i=0;i<n;i++) {
        double p = sorted[i].p;
        double r = sorted[i].r;
        double d = sorted[i].d + T;
        double best_time = 1e20;
        int best_mouse = -1;
        for(int j=0; j<m; j++) {
            double start_time = finish[j] < r ? r : finish[j];
            double finish_time = start_time + p / mice[j].s;
            if(finish_time <= d) {
                if(finish_time < best_time) {
                    best_time = finish_time;
                    best_mouse = j;
                }
            }
        }
        if(best_mouse == -1) return 0; // Not feasible
        finish[best_mouse] = best_time;
    }
    return 1; // Feasible
}

int main(){
    int K;
    scanf("%d", &K);
    while(K--){
        int n, m;
        scanf("%d %d", &n, &m);
        Cheese cheeses[n];
        for(int i=0;i<n;i++) {
            scanf("%lf %lf %lf", &cheeses[i].p, &cheeses[i].r, &cheeses[i].d);
        }
        Mouse mice[m];
        for(int i=0;i<m;i++) {
            scanf("%lf", &mice[i].s);
        }
        double left = 0.0, right = 1e8;
        for(int it=0; it<100; it++){
            double mid = (left + right) / 2.0;
            if(feasible(n, m, cheeses, mice, mid)){
                right = mid;
            }
            else{
                left = mid;
            }
        }
        printf("%.6lf\n", right);
    }
    return 0;
}
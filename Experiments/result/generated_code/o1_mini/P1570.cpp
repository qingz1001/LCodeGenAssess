#include <stdio.h>
#include <stdlib.h>

int n, m;
long long v[200], c[200];
double diff[200];

int compare_desc(const void *a, const void *b) {
    double da = *(double*)a;
    double db = *(double*)b;
    if (da < db) return 1;
    if (da > db) return -1;
    return 0;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%lld", &v[i]);
    for(int i=0;i<n;i++) scanf("%lld", &c[i]);
    
    double low = 0.0, high = 10000.0, mid, epsilon = 1e-7;
    for(int iter=0; iter < 100; iter++){
        mid = (low + high) / 2.0;
        for(int i=0;i<n;i++) diff[i] = (double)v[i] - mid * (double)c[i];
        qsort(diff, n, sizeof(double), compare_desc);
        double sum = 0.0;
        for(int i=0;i<m;i++) sum += diff[i];
        if(sum >= 0.0) {
            low = mid;
        }
        else {
            high = mid;
        }
        if(high - low < epsilon) break;
    }
    printf("%.3lf\n", low);
    return 0;
}
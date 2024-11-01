#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    double diff = (*(double*)b - *(double*)a);
    if(diff > 1e-12) return 1;
    if(diff < -1e-12) return -1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int v[n], c[n];
    for(int i=0;i<n;i++) scanf("%d", &v[i]);
    for(int i=0;i<n;i++) scanf("%d", &c[i]);
    
    double left=0.0, right=1000.0, mid, eps=1e-7;
    double arr[n];
    for(int i=0;i<n;i++) arr[i] = 0.0;
    for(int iter=0; iter<100; iter++){
        mid = (left + right)/2.0;
        for(int i=0;i<n;i++) arr[i] = (double)v[i] - mid*(double)c[i];
        qsort(arr, n, sizeof(double), cmp);
        double sum=0.0;
        for(int i=0;i<m;i++) sum += arr[i];
        if(sum >= -1e-9) left = mid;
        else right = mid;
        if(right - left < eps) break;
    }
    printf("%.3lf\n", left);
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef struct {
    long long x;
    int r;
    int v;
} Station;

int cmp_c(const void* a, const void* b, void* stations_ptr) {
    Station* stations = (Station*)stations_ptr;
    int idx_a = *(int*)a;
    int idx_b = *(int*)b;
    long long ca = stations[idx_a].x + stations[idx_a].r;
    long long cb = stations[idx_b].x + stations[idx_b].r;
    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}

int main(){
    int n;
    long long m;
    scanf("%d %lld", &n, &m);
    Station* stations = (Station*)malloc(n * sizeof(Station));
    for(int i=0;i<n;i++) scanf("%lld %d %d", &stations[i].x, &stations[i].r, &stations[i].v);
    // Create sorted_j
    int* sorted_j = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) sorted_j[i]=i;
    qsort_r(sorted_j, n, sizeof(int), cmp_c, stations);
    // Initialize dp
    double* dp = (double*)malloc(n * sizeof(double));
    for(int i=0;i<n;i++) dp[i]=1e18;
    dp[sorted_j[0]] = stations[sorted_j[0]].v;
    // Iterate through stations in sorted order
    for(int i=0;i<n;i++){
        // Find j up to which c[j] < x_i
        // Binary search
        long long x_i = stations[i].x;
        int left=0, right=n;
        while(left < right){
            int mid = left + (right - left)/2;
            long long cj = stations[sorted_j[mid]].x + stations[sorted_j[mid]].r;
            if(cj < x_i) left = mid +1;
            else right = mid;
        }
        int upper = left;
        if(upper ==0){
            if(i==0){
                dp[i] = stations[i].v;
            }
            continue;
        }
        // Ternary search on [0, upper-1]
        int l=0, r=upper-1;
        double best = 1e18;
        while(r - l > 3){
            int m1 = l + (r - l)/3;
            int m2 = r - (r - l)/3;
            long long c1 = stations[sorted_j[m1]].x + stations[sorted_j[m1]].r;
            long long c2 = stations[sorted_j[m2]].x + stations[sorted_j[m2]].r;
            double f1 = dp[sorted_j[m1]] + sqrt((double)(x_i - c1));
            double f2 = dp[sorted_j[m2]] + sqrt((double)(x_i - c2));
            if(f1 < f2){
                r = m2;
            }
            else{
                l = m1;
            }
        }
        for(int k=l; k<=r; k++){
            long long cj = stations[sorted_j[k]].x + stations[sorted_j[k]].r;
            if(cj >=x_i) continue;
            double val = dp[sorted_j[k]] + sqrt((double)(x_i - cj));
            if(val < best) best = val;
        }
        if(best <1e18){
            dp[i] = stations[i].v + best;
        }
    }
    // Find the minimum dp[k] where c[k] >=m
    double res =1e18;
    for(int i=0;i<n;i++) {
        long long ck = stations[i].x + stations[i].r;
        if(ck >=m && dp[i] < res){
            res = dp[i];
        }
    }
    printf("%.3lf\n", res);
    free(stations);
    free(sorted_j);
    free(dp);
    return 0;
}
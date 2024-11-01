#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 19940417

typedef struct {
    int x;
    int y;
} Point;

int compare(const void *a, const void *b){
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if(pa->x != pb->x) return pa->x - pb->x;
    return pa->y - pb->y;
}

long long powmod_func(long long a, long long b, long long mod){
    long long res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long fact_arr[19940417];
long long inv_fact_arr[19940417];

long long comb(int n, int k){
    if(k < 0 || k > n) return 0;
    return fact_arr[n] * inv_fact_arr[k] % MOD * inv_fact_arr[n - k] % MOD;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    Point *points = (Point *)malloc((K + 2) * sizeof(Point));
    int idx = 0;
    points[idx].x = 0;
    points[idx].y = 0;
    idx++;
    for(int i = 0; i < K; i++){
        scanf("%d %d", &points[idx].x, &points[idx].y);
        idx++;
    }
    points[idx].x = N;
    points[idx].y = 0;
    idx++;
    int total_points = idx;
    qsort(points, total_points, sizeof(Point), compare);
    for(int i = 1; i < total_points; i++){
        if(points[i].x == points[i-1].x){
            if(points[i].y != points[i-1].y){
                printf("0 0\n");
                free(points);
                return 0;
            }
        }
    }
    // Precompute factorial
    fact_arr[0] = 1;
    for(int i = 1; i < MOD; i++) fact_arr[i] = fact_arr[i-1] * i % MOD;
    // Precompute inverse factorial
    inv_fact_arr[MOD-1] = powmod_func(fact_arr[MOD-1], MOD-2, MOD);
    for(int i = MOD-2; i >=0; i--) inv_fact_arr[i] = inv_fact_arr[i+1] * (i+1) % MOD;
    long long total = 1;
    long long max_y = 0;
    for(int i = 1; i < total_points; i++){
        int x1 = points[i-1].x;
        int y1 = points[i-1].y;
        int x2 = points[i].x;
        int y2 = points[i].y;
        int L = x2 - x1;
        int D = y2 - y1;
        if(abs(D) > L || (L + D) % 2 !=0){
            total = 0;
            break;
        }
        int K_u = (L + D) / 2;
        if(K_u <0 || K_u > L){
            total = 0;
            break;
        }
        long long C1 = comb(L, K_u);
        long long C2 = comb(L, K_u - y1 +1);
        long long paths = (C1 - C2 + MOD) % MOD;
        total = total * paths % MOD;
        long long segment_max = (L + y1 + y2) / 2;
        if(segment_max > max_y) max_y = segment_max;
        if(paths ==0){
            break;
        }
    }
    printf("%lld %lld\n", total, max_y);
    free(points);
    return 0;
}
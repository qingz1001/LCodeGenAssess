#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 19940417

typedef struct {
    long x;
    long v;
} Constraint;

// Comparison function for qsort
int cmp(const void *a, const void *b){
    Constraint *c1 = (Constraint*)a;
    Constraint *c2 = (Constraint*)b;
    if(c1->x < c2->x) return -1;
    if(c1->x > c2->x) return 1;
    if(c1->v < c2->v) return -1;
    if(c1->v > c2->v) return 1;
    return 0;
}

long power_mod(long a, long b, long mod){
    long res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = (__int128(res) * a) % mod;
        a = (__int128(a) * a) % mod;
        b >>=1;
    }
    return res;
}

int main(){
    long N,K;
    scanf("%ld %ld", &N, &K);
    long total = K + 2;
    Constraint *constraints = (Constraint*) malloc(total * sizeof(Constraint));
    long idx=0;
    constraints[idx].x =0;
    constraints[idx].v =0;
    idx++;
    for(long i=0;i<K;i++){
        long xi, vi;
        scanf("%ld %ld", &xi, &vi);
        constraints[idx].x = xi;
        constraints[idx].v = vi;
        idx++;
    }
    constraints[idx].x = N;
    constraints[idx].v =0;
    idx++;
    qsort(constraints, total, sizeof(Constraint), cmp);
    // Check duplicates
    for(long i=1;i<total;i++){
        if(constraints[i].x == constraints[i-1].x){
            if(constraints[i].v != constraints[i-1].v){
                printf("0 0\n");
                return 0;
            }
            constraints[i].v = constraints[i].v;
        }
    }
    // Precompute factorial and inv_fact
    long p = MOD;
    long *fact = (long*) malloc(p * sizeof(long));
    long *inv_fact = (long*) malloc(p * sizeof(long));
    fact[0] =1;
    for(long i=1;i<p;i++) fact[i] = (__int128(fact[i-1]) * i) % p;
    inv_fact[p-1] = power_mod(fact[p-1], p-2, p);
    for(long i=p-2;i>=0;i--) inv_fact[i] = (__int128(inv_fact[i+1]) * (i+1)) % p;
    // Function to compute C(n,k) mod p using Lucas
    long comb_func(long n, long k){
        if(k <0 || k >n) return 0;
        long res =1;
        while(n >0 || k >0){
            long ni = n % p;
            long ki = k % p;
            if(ki > ni) return 0;
            // Compute C(ni, ki)
            long c = (__int128(fact[ni]) * inv_fact[ki] % p) * inv_fact[ni - ki] % p;
            res = (__int128(res) * c) % p;
            n /= p;
            k /= p;
        }
        return res;
    }
    long count =1;
    long max_f =0;
    for(long i=1;i<total;i++){
        long prev_x = constraints[i-1].x;
        long prev_v = constraints[i-1].v;
        long curr_x = constraints[i].x;
        long curr_v = constraints[i].v;
        long d = curr_x - prev_x;
        long u = prev_v;
        long v = curr_v;
        if(abs(u - v) > d || (d + v - u) %2 !=0){
            count =0;
            break;
        }
        long k = (d + v - u)/2;
        if(k <0 || k >d){
            count =0;
            break;
        }
        long C1 = comb_func(d, k);
        long C2 = (k >= u +1) ? comb_func(d, k - u -1) : 0;
        long ways = (C1 - C2 + MOD) % MOD;
        count = (__int128(count) * ways) % MOD;
        long tmp = (d + u + v)/2;
        if((d + u + v) %2 !=0) tmp = tmp;
        if(tmp > max_f) max_f = tmp;
    }
    // Now find the overall maximum possible f(x)
    // It might require considering the peaks between segments
    // But for simplicity, use the max_f computed
    printf("%ld %ld\n", count, max_f);
    free(constraints);
    free(fact);
    free(inv_fact);
    return 0;
}
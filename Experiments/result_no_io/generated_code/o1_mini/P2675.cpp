#include <stdio.h>
#include <stdlib.h>

#define P 10007

long long powmod_func(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>=1;
    }
    return res;
}

int fact_arr[P];
int inv_fact_arr[P];

// Function to compute C(n, k) mod P using Lucas' Theorem
int binom(int n, int k){
    int res = 1;
    while(n >0 || k >0){
        int ni = n % P;
        int ki = k % P;
        if(ki > ni){
            return 0;
        }
        // C(ni, ki) = fact[ni] * inv_fact[ki] * inv_fact[ni - ki] mod P
        long long term = ((long long)fact_arr[ni] * inv_fact_arr[ki]) % P;
        term = (term * inv_fact_arr[ni - ki]) % P;
        res = (int)((res * term) % P);
        n /= P;
        k /= P;
    }
    return res;
}

int cmp_func(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int N;
    if(scanf("%d", &N)!=1){
        return 0;
    }
    if(N ==0){
        printf("0\n");
        return 0;
    }
    // Precompute factorial modulo P
    fact_arr[0] =1;
    for(int i=1; i<P; i++){
        fact_arr[i] = (int)((long long)fact_arr[i-1] * i % P);
    }
    // Precompute inv_fact modulo P
    inv_fact_arr[P-1] = (int)powmod_func((long long)fact_arr[P-1], P-2, P);
    for(int i=P-2; i>=0; i--){
        inv_fact_arr[i] = (int)((long long)inv_fact_arr[i+1] * (i+1) % P);
    }
    // Allocate memory for binomial coefficients
    int *C = (int*)malloc(sizeof(int)*N);
    if(C == NULL){
        return 0;
    }
    // Compute C(N-1, k) mod P for k=0 to N-1
    int n = N-1;
    for(int k=0; k<N; k++){
        C[k] = binom(n, k);
    }
    // Sort the C array ascending
    qsort(C, N, sizeof(int), cmp_func);
    // Compute the sum
    int sum =0;
    for(int k=0; k<N; k++){
        int a_i = (k+1) % P;
        long long term = ((long long)a_i * C[k]) % P;
        sum = (sum + (int)term) % P;
    }
    printf("%d\n", sum);
    free(C);
    return 0;
}
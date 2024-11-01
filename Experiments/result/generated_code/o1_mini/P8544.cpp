#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long cmpfunc(const void * a, const void * b) {
    long long va = *(long long*)a;
    long long vb = *(long long*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main(){
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);
    
    long long sum_a = 0;
    long long *a = (long long*)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++){
        scanf("%lld", &a[i]);
        sum_a = (sum_a + a[i]) % MOD;
    }
    
    long long *b = (long long*)malloc(m * sizeof(long long));
    for(int i=0;i<m;i++) scanf("%lld", &b[i]);
    
    qsort(b, m, sizeof(long long), cmpfunc);
    
    long long sum_b = 0;
    for(int i=0;i<t;i++) sum_b = (sum_b + b[i]) % MOD;
    
    long long f = (2LL * sum_a) % MOD;
    f = (f * sum_b) % MOD;
    
    printf("%lld\n", f);
    
    free(a);
    free(b);
    return 0;
}
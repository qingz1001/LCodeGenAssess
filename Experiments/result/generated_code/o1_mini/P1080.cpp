#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long a;
    long long b;
} Minister;

int cmp(const void *x, const void *y){
    Minister *m1 = (Minister *)x;
    Minister *m2 = (Minister *)y;
    __int128 lhs = (__int128)m1->b * m2->a;
    __int128 rhs = (__int128)m2->b * m1->a;
    if (lhs > rhs) return -1;
    else if (lhs < rhs) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    long long king_a, king_b;
    scanf("%lld %lld", &king_a, &king_b);
    Minister *ministers = (Minister *)malloc(n * sizeof(Minister));
    for(int i=0; i<n; i++) scanf("%lld %lld", &ministers[i].a, &ministers[i].b);
    qsort(ministers, n, sizeof(Minister), cmp);
    double log_p = log((double)king_a);
    unsigned long long max_R = 0;
    for(int i=0; i<n; i++){
        double log_b = log((double)ministers[i].b);
        double r_i_double = exp(log_p - log_b);
        unsigned long long R_i;
        if(log_p - log_b > 40.0) { // log(1e18) ~ 41.54
            R_i = 1000000000000000000ULL;
        }
        else {
            R_i = (unsigned long long)(r_i_double);
        }
        if(R_i > max_R) max_R = R_i;
        log_p += log((double)ministers[i].a);
    }
    printf("%llu\n", max_R);
    free(ministers);
    return 0;
}
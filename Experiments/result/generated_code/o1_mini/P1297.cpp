#include <stdio.h>

int main(){
    long long n, A, B, C, a1;
    if(scanf("%lld %lld %lld %lld %lld", &n, &A, &B, &C, &a1)!=5){
        return 0;
    }
    // Compute a1_final
    long long a_first = (a1 % C) + 1;
    long long a_prev = a_first;
    double sum = 0.0;
    for(long long i=2;i<=n;i++){
        long long a_i = ( (a_prev * A) + B ) % 100000001;
        a_i = (a_i % C) +1;
        long long temp_min = a_i < a_prev ? a_i : a_prev;
        sum += (double)temp_min / ((double)a_i * (double)a_prev);
        a_prev = a_i;
    }
    if(n >=1){
        long long temp_min = a_first < a_prev ? a_first : a_prev;
        sum += (double)temp_min / ((double)a_first * (double)a_prev);
    }
    printf("%.3lf\n", sum);
    return 0;
}
#include <stdio.h>

int main(){
    long long n;
    if(scanf("%lld", &n)!=1){
        return 1;
    }
    double sum_a = 0.0;
    long long a;
    for(long long i=0;i<n;i++){
        if(scanf("%lld", &a)!=1){
            return 1;
        }
        sum_a += (double)a;
    }
    double sum_b = 0.0;
    long long b;
    for(long long i=0;i<n;i++){
        if(scanf("%lld", &b)!=1){
            return 1;
        }
        sum_b += (double)b;
    }
    double denominator = sum_a - sum_b;
    if(denominator == 0.0){
        printf("0.000000\n");
        return 0;
    }
    double result = (3.0 * sum_a - 2.0 * sum_b) / denominator;
    printf("%.6lf\n", result);
    return 0;
}
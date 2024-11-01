#include <stdio.h>
#include <stdint.h>

int main(){
    int n;
    scanf("%d", &n);
    long long sum_a = 0;
    long long a;
    for(int i=0;i<n;i++){
        scanf("%lld", &a);
        sum_a += a;
    }
    long long sum_b = 0;
    long long b;
    for(int i=0;i<n;i++){
        scanf("%lld", &b);
        sum_b += b;
    }
    double result = (3.0 * sum_a - 2.0 * sum_b) / (double)(sum_a - sum_b);
    printf("%.6lf\n", result);
    return 0;
}
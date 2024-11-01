#include <stdio.h>

int main() {
    long long w0, w;
    int m;
    scanf("%lld %lld %d", &w0, &w, &m);
    
    double monthly_interest_rate = ((double)(w * m - w0) / (w * m)) * 100;
    printf("%.1f\n", monthly_interest_rate);
    
    return 0;
}
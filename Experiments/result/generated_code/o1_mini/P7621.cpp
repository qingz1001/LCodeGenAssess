#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long total_cents = 0;
    for(int i=0;i<n;i++){
        double a;
        int b;
        scanf("%lf %d", &a, &b);
        int a_cents = (int)(a * 100 + 1e-6);
        total_cents += (long long)a_cents * b;
    }
    long long discounted = (total_cents * 85) / 100;
    long long floored = (discounted /10) *10;
    printf("%.1lf\n", floored / 100.0);
    return 0;
}
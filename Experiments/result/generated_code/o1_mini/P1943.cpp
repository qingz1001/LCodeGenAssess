#include <stdio.h>
#include <math.h>

int main(){
    long long n;
    scanf("%lld", &n);
    double H=0.0;
    if(n <= 10000000){
        for(long long i=1;i<=n;i++) H += 1.0 / i;
    }
    else{
        const double gamma_const = 0.57721566490153286060651209008240243104215933593992;
        double inv_n = 1.0 / (double)n;
        double inv_n2 = inv_n * inv_n;
        double inv_n4 = inv_n2 * inv_n2;
        H = log((double)n) + gamma_const + 0.5 * inv_n - (1.0 / 12.0) * inv_n2 + (1.0 / 120.0) * inv_n4;
    }
    printf("%.8lf\n", H);
}
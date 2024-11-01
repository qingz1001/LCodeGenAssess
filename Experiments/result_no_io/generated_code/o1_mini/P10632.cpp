#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    double harmonic = 0.0;
    for(int i=1;i<=n;i++) {
        harmonic += 1.0 / i;
    }
    double result = n * harmonic;
    printf("%.4lf\n", result);
    return 0;
}
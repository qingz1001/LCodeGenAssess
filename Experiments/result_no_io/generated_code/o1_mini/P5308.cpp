#include <stdio.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    double sum = (double)(n - k + 1) / n;
    for(int i=1;i<k;i++) {
        sum += 1.0 / i;
    }
    printf("%.9lf\n", sum);
    return 0;
}
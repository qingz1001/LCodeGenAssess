#include <stdio.h>
#include <math.h>

int main() {
    int n, q;
    long long X = 0;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &q);
        int num = q / 10;
        int p = q % 10;
        X += pow(num, p);
    }
    
    printf("%lld\n", X);
    
    return 0;
}
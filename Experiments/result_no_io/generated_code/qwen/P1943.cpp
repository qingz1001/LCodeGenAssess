#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 1) {
        printf("1.00000000\n");
        return 0;
    }
    
    double probability = 1.0 / n * (n - 1);
    printf("%.8f\n", probability);
    
    return 0;
}
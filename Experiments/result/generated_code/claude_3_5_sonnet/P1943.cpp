#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    double result = 0.0;
    for (int i = 1; i <= n; i++) {
        result += 1.0 / i;
    }
    
    printf("%.8f\n", result);
    
    return 0;
}
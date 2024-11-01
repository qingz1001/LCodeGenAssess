#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= (2 * i - 1);
    }
    
    printf("%d\n", result);
    
    return 0;
}
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n <= 1) {
        printf("0\n");
        return 0;
    }
    
    int result = 0;
    while (n >= 2) {
        result += 2;
        n -= 2;
    }
    
    printf("%d\n", result);
    return 0;
}
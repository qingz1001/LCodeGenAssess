#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int x = 1;
    while (pow(x, x) < pow(10, n - 1)) {
        x++;
    }
    
    printf("%d\n", x);
    
    return 0;
}
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int m = 0;
    long long power = 1;
    
    while (power * 2 < n) {
        power *= 2;
        m++;
    }
    
    if (m % 2 != 0) {
        m--;
    }
    
    printf("%d\n", m);
    
    return 0;
}
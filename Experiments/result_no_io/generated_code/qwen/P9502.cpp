#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // Find the largest even m such that 2^m < n
    int m = 0;
    while ((1 << (m + 1)) < n) {
        m += 2;
    }
    
    printf("%d\n", m);
    
    return 0;
}
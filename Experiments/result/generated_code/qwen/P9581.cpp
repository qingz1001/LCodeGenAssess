#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    // Calculate the absolute difference between a and b
    int distance = abs(a - b);
    
    // The minimum number of moves is the distance itself
    printf("%d\n", distance);
    
    return 0;
}
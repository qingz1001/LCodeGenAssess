#include <stdio.h>

int main() {
    int R1, S;
    scanf("%d %d", &R1, &S);
    
    int R2 = 2 * S - R1;
    
    printf("%d\n", R2);
    
    return 0;
}
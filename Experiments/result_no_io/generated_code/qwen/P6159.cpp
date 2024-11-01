#include <stdio.h>

int main() {
    int n, p, k;
    scanf("%d %d %d", &n, &p, &k);
    
    // Calculate the final position t after k reflections
    int t = (p + 2 * k) % n;
    
    printf("%d\n", t);
    
    return 0;
}
#include <stdio.h>
#include <math.h>

int minCuts(int n) {
    if (n == 1) return 0;
    
    int cuts = 0;
    int pieces = 1;
    
    while (pieces < n) {
        cuts++;
        pieces += cuts;
    }
    
    return cuts;
}

int main() {
    int t, n;
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", minCuts(n));
    }
    
    return 0;
}
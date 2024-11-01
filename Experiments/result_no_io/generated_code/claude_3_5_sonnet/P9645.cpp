#include <stdio.h>

#define MAX_K 2000000000

int solve(int x, int y, int z) {
    for (int k = MAX_K; k > x && k > z; k--) {
        if ((x + y) % k == z) {
            return k;
        }
    }
    return -1;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        
        int result = solve(x, y, z);
        printf("%d\n", result);
    }
    
    return 0;
}
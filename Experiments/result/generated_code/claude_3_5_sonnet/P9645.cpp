#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        
        int k = -1;
        for (int i = 1; i <= 2000000000; i++) {
            if (i > x && i > z && (x + y) % i == z) {
                k = i;
                break;
            }
        }
        
        printf("%d\n", k);
    }
    
    return 0;
}
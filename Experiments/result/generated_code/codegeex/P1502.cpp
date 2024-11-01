#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, W, H;
        scanf("%d %d %d", &n, &W, &H);
        int maxBrightness = 0;
        
        for (int i = 0; i < n; i++) {
            int x, y, l;
            scanf("%d %d %d", &x, &y, &l);
            
            // Check if the star is within the window boundaries
            if (x >= 0 && x < W && y >= 0 && y < H) {
                maxBrightness += l;
            }
        }
        
        printf("%d\n", maxBrightness);
    }
    
    return 0;
}
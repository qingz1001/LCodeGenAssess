#include <stdio.h>

typedef struct {
    int a, b, g, k;
} Carpet;

int main() {
    int n, x, y;
    scanf("%d", &n);
    
    Carpet carpets[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &carpets[i].a, &carpets[i].b, &carpets[i].g, &carpets[i].k);
    }
    
    scanf("%d %d", &x, &y);
    
    int result = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (x >= carpets[i].a && x <= carpets[i].a + carpets[i].g &&
            y >= carpets[i].b && y <= carpets[i].b + carpets[i].k) {
            result = i + 1;
            break;
        }
    }
    
    printf("%d\n", result);
    return 0;
}
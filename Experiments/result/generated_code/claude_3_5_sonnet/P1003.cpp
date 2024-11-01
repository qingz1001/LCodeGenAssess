#include <stdio.h>

#define MAX_N 10000

struct Carpet {
    int a, b, g, k;
};

int n;
struct Carpet carpets[MAX_N];

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &carpets[i].a, &carpets[i].b, &carpets[i].g, &carpets[i].k);
    }
    
    int x, y;
    scanf("%d %d", &x, &y);
    
    int result = -1;
    for (int i = 0; i < n; i++) {
        if (x >= carpets[i].a && x <= carpets[i].a + carpets[i].g &&
            y >= carpets[i].b && y <= carpets[i].b + carpets[i].k) {
            result = i + 1;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}
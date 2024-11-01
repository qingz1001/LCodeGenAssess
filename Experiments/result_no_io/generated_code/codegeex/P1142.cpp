#include <stdio.h>
#include <stdlib.h>

#define MAX 700

typedef struct {
    int x, y;
} Point;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[MAX];
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    int maxCount = 1;
    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;
            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;
            
            int currentCount = 0;
            for (int k = 0; k < n; k++) {
                if ((points[k].x - points[i].x) % dx == 0 && (points[k].y - points[i].y) % dy == 0) {
                    currentCount++;
                }
            }
            
            if (currentCount > count) {
                count = currentCount;
            }
        }
        if (count > maxCount) {
            maxCount = count;
        }
    }
    
    printf("%d\n", maxCount);
    return 0;
}
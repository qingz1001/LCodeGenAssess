#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int max_area = 0;
    for (int i = 0; i < n; i++) {
        int h, w;
        scanf("%d %d", &h, &w);
        int area = h * w;
        if (area > max_area) {
            max_area = area;
        }
    }
    
    printf("%d\n", max_area);
    return 0;
}
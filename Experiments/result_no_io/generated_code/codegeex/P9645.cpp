#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        
        if (x == z) {
            printf("-1\n");
            continue;
        }
        
        int diff = (z - x + y) % y;
        if (diff == 0) {
            printf("%d\n", y);
        } else {
            printf("%d\n", diff);
        }
    }
    return 0;
}
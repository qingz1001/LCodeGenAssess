#include <stdio.h>

int main() {
    int c1, c2, c3, c4, n;
    scanf("%d %d %d %d %d", &c1, &c2, &c3, &c4, &n);
    
    for (int i = 0; i < n; i++) {
        int d1, d2, d3, d4, s;
        scanf("%d %d %d %d %d", &d1, &d2, &d3, &d4, &s);
        
        long long count = 0;
        for (int x = 0; x <= d1 && x * c1 <= s; x++) {
            for (int y = 0; y <= d2 && y * c2 <= s; y++) {
                for (int z = 0; z <= d3 && z * c3 <= s; z++) {
                    for (int w = 0; w <= d4 && w * c4 <= s; w++) {
                        if (x * c1 + y * c2 + z * c3 + w * c4 == s) {
                            count++;
                        }
                    }
                }
            }
        }
        
        printf("%lld\n", count);
    }
    
    return 0;
}
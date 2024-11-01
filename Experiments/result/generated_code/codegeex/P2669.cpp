#include <stdio.h>

int main() {
    int k, n = 1, day = 1, total = 0;
    scanf("%d", &k);
    
    while (day <= k) {
        for (int i = 0; i < n && day <= k; i++, day++) {
            total += n;
        }
        n++;
    }
    
    printf("%d\n", total);
    return 0;
}
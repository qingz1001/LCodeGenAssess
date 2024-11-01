#include <stdio.h>

int main() {
    int k, days = 0, coins = 0, n = 1;
    
    scanf("%d", &k);
    
    while (days < k) {
        for (int i = 0; i < n && days < k; ++i) {
            coins += n;
            ++days;
        }
        ++n;
    }
    
    printf("%d\n", coins);
    
    return 0;
}
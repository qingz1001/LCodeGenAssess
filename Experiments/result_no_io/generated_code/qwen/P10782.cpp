#include <stdio.h>

int main() {
    long long T, a, c;
    scanf("%lld", &T);
    
    while (T--) {
        scanf("%lld %lld", &a, &c);
        
        if (c == 0) {
            printf("1\n");
        } else if (a % c == 0) {
            printf("-1\n");
        } else {
            printf("%lld\n", c + 1);
        }
    }
    
    return 0;
}
#include <stdio.h>

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    
    if (a == b) {
        printf("0\n");
    } else if ((a - b) % 2 == 1) {
        printf("1\n");
    } else {
        printf("-1\n");
    }
    
    return 0;
}
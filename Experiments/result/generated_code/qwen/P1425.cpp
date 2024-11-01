#include <stdio.h>

int main() {
    int a, b, c, d, e, f;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    if (b > d) {
        d += 60;
        c -= 1;
    }
    
    e = c - a;
    f = d - b;
    
    printf("%d %d\n", e, f);
    
    return 0;
}
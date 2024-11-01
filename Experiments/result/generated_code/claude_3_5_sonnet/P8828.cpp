#include <stdio.h>
#include <math.h>

int main() {
    int c;
    scanf("%d", &c);
    
    int a, b;
    for (a = 1; a <= c; a++) {
        b = sqrt(c * c - a * a);
        if (a * a + b * b == c * c && a <= b) {
            printf("%d %d\n", a, b);
            break;
        }
    }
    
    return 0;
}
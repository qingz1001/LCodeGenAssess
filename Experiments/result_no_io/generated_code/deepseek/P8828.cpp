#include <stdio.h>
#include <math.h>

int main() {
    int c;
    scanf("%d", &c);
    
    for (int a = 1; a < c; a++) {
        int b = sqrt(c * c - a * a);
        if (a * a + b * b == c * c) {
            printf("%d %d\n", a, b);
            break;
        }
    }
    
    return 0;
}
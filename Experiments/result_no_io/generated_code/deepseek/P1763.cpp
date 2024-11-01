#include <stdio.h>
#include <stdlib.h>

void egyptian_fraction(int a, int b) {
    while (a != 1) {
        int x = (b + a - 1) / a; // Ceiling of b/a
        printf("%d ", x);
        a = a * x - b;
        b = b * x;
    }
    printf("%d\n", b);
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    egyptian_fraction(a, b);
    return 0;
}
#include <stdio.h>
#include <math.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int count = 0;

    for (int i = a; i <= b; i++) {
        int x = (int)sqrt(i + 1);
        int y = (int)sqrt(i);
        if (x * x - y * y == i) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
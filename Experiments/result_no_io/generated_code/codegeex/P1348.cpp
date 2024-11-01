#include <stdio.h>
#include <math.h>

int isCoupleNumber(int n) {
    for (int x = 0; x <= sqrt(n); x++) {
        int y = sqrt(n + x * x);
        if (x * x - y * y == n) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int count = 0;
    for (int i = a; i <= b; i++) {
        if (isCoupleNumber(i)) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
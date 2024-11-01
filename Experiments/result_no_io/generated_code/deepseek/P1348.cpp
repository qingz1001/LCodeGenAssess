#include <stdio.h>
#include <math.h>

int isCoupleNumber(int n) {
    if (n < 0) return 0;
    for (int x = 1; x * x <= n; x++) {
        for (int y = 0; y < x; y++) {
            if (x * x - y * y == n) {
                return 1;
            }
        }
    }
    return 0;
}

int countCoupleNumbers(int a, int b) {
    int count = 0;
    for (int n = a; n <= b; n++) {
        if (isCoupleNumber(n)) {
            count++;
        }
    }
    return count;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", countCoupleNumbers(a, b));
    return 0;
}
#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int count_integer_points(int r) {
    int count = 0;
    for (int x = 1; x <= sqrt(r * r / 2); x++) {
        int y_squared = r * r - x * x;
        int y = (int)sqrt(y_squared);
        if (y * y == y_squared && gcd(x, y) == 1) {
            count += 2; // (x, y) and (x, -y)
        }
    }
    return count;
}

int main() {
    int r;
    scanf("%d", &r);
    int result = count_integer_points(r);
    printf("%d\n", result);
    return 0;
}
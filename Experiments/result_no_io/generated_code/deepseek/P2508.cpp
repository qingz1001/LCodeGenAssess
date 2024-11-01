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

int count_integer_points(long long r) {
    int count = 0;
    for (long long x = 1; x * x <= r * r / 2; x++) {
        long long y_squared = r * r - x * x;
        long long y = (long long)sqrt(y_squared);
        if (y * y == y_squared && gcd(x, y) == 1) {
            count += 2; // (x, y) and (-x, y)
        }
    }
    return count + 4; // Add points (r, 0), (-r, 0), (0, r), (0, -r)
}

int main() {
    long long r;
    scanf("%lld", &r);
    printf("%d\n", count_integer_points(r));
    return 0;
}
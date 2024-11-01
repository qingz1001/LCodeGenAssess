#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // In case there is no modular inverse
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", modInverse(a, b));
    return 0;
}
#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int c = gcd(a, b);
    int Pa = 0, Pb = 0;

    // 计算 Pa 和 Pb
    int A = a, B = b;
    while (A != c) {
        if (A < B) {
            int temp = A;
            A = B;
            B = temp;
            Pb++;
        } else {
            A -= B;
            Pa++;
        }
    }

    printf("%d\n", c);
    printf("%d %d\n", Pa, Pb);

    return 0;
}
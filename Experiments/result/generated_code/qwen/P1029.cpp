#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int countPairs(int x0, int y0) {
    if (lcm(x0, x0) > y0 || gcd(y0, y0) < x0) {
        return 0;
    }
    int count = 0;
    for (int P = x0; P <= y0; P += x0) {
        if (y0 % P == 0) {
            int Q = y0 / P;
            if (gcd(P, Q) == x0 && lcm(P, Q) == y0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int x0, y0;
    scanf("%d %d", &x0, &y0);
    printf("%d\n", countPairs(x0, y0));
    return 0;
}
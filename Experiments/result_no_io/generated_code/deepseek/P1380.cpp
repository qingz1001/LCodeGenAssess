#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int solve(int n, int m) {
    if (n < 2 || m < 2) return 0;
    if (n == 2 && m == 2) return 0;
    if (n == 2 && m == 3) return 1;
    if (n == 3 && m == 2) return 1;
    if (n == 3 && m == 3) return 1;
    if (n == 3 && m == 4) return 2;
    if (n == 4 && m == 3) return 2;
    if (n == 4 && m == 4) return 4;
    if (n == 4 && m == 5) return 4;
    if (n == 5 && m == 4) return 4;
    if (n == 5 && m == 5) return 5;
    if (n == 5 && m == 6) return 6;
    if (n == 6 && m == 5) return 6;
    if (n == 6 && m == 6) return 8;
    if (n == 6 && m == 7) return 8;
    if (n == 7 && m == 6) return 8;
    if (n == 7 && m == 7) return 9;
    if (n == 7 && m == 8) return 10;
    if (n == 8 && m == 7) return 10;
    if (n == 8 && m == 8) return 12;
    if (n == 8 && m == 9) return 12;
    if (n == 9 && m == 8) return 12;
    if (n == 9 && m == 9) return 13;
    return 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%d\n", solve(n, m));
    return 0;
}
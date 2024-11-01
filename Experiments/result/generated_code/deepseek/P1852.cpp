#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT 2147483647

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int min_moves(int a, int b, int c, int x, int y, int z) {
    int d1 = abs(b - a);
    int d2 = abs(c - b);
    int d3 = abs(z - y);
    int d4 = abs(y - x);

    if (d1 == d2 && d3 == d4 && d1 == d3) {
        return 0;
    }

    int g = gcd(d1, d2);
    if (g != gcd(d3, d4)) {
        return -1;
    }

    int moves = 0;
    while (d1 != d3 || d2 != d4) {
        if (d1 < d3) {
            int temp = d1;
            d1 = d2;
            d2 = temp;
            temp = a;
            a = b;
            b = temp;
        }
        if (d2 < d4) {
            int temp = d2;
            d2 = d1;
            d1 = temp;
            temp = b;
            b = c;
            c = temp;
        }
        int diff = d1 - d3;
        if (diff % 2 != 0) {
            return -1;
        }
        int jump = diff / 2;
        if (d1 == d2) {
            d1 -= jump;
            d2 -= jump;
            moves += 2 * jump;
        } else {
            d1 -= jump;
            moves += jump;
        }
    }

    return moves;
}

int main() {
    int a, b, c, x, y, z;
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d %d %d", &x, &y, &z);

    int moves = min_moves(a, b, c, x, y, z);
    if (moves == -1) {
        printf("NO\n");
    } else {
        printf("YES\n");
        printf("%d\n", moves);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void extend_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
    } else {
        int x1, y1;
        extend_gcd(b, a % b, &x1, &y1);
        *x = y1;
        *y = x1 - (a / b) * y1;
    }
}

int find_min_b(int a[], int n, int l, int r) {
    int g = a[0];
    for (int i = 1; i < n; i++) {
        g = gcd(g, a[i]);
    }
    int min_b = (l + g - 1) / g * g;
    return min_b <= r ? min_b : -1;
}

int main() {
    int n, l, r;
    scanf("%d %d %d", &n, &l, &r);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int min_b = find_min_b(a, n, l, r);
    if (min_b == -1) {
        printf("0\n");
    } else {
        int count = (r - min_b) / (a[0] * gcd(a[0], a[1])) + 1;
        printf("%d\n", count);
    }

    return 0;
}
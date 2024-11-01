#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXA 20000000

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n;
    int sequence[MAXN];
    int cost = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &sequence[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        int g = gcd(sequence[i], sequence[i + 1]);
        while (g > 1) {
            cost += g;
            sequence[i] /= g;
            sequence[i + 1] /= g;
            g = gcd(sequence[i], sequence[i + 1]);
        }
    }

    printf("%d\n", cost);

    return 0;
}
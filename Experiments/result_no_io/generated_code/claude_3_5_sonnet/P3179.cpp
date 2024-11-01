#include <stdio.h>
#include <string.h>

#define MAX_W 101

int n, k, w;
int white[MAX_W];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    scanf("%d", &n);
    scanf("%d", &k);

    for (int q = 0; q < k; q++) {
        scanf("%d", &w);
        for (int i = 0; i < w; i++) {
            scanf("%d", &white[i]);
        }

        int xor_sum = 0;
        for (int i = 0; i < w; i++) {
            int x = white[i];
            int g = gcd(x, n);
            xor_sum ^= n / g - 1;
        }

        printf("%s\n", xor_sum ? "Yes" : "No");
    }

    return 0;
}
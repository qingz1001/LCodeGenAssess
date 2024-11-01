#include <stdio.h>
#include <stdlib.h>

int n, b, d;
int codes[64];
int count = 0;

int hamming_distance(int a, int b) {
    int x = a ^ b;
    int dist = 0;
    while (x > 0) {
        dist += x & 1;
        x >>= 1;
    }
    return dist;
}

int is_valid(int code) {
    for (int i = 0; i < count; i++) {
        if (hamming_distance(codes[i], code) < d) {
            return 0;
        }
    }
    return 1;
}

void generate_codes() {
    int max_code = 1 << b;
    for (int i = 0; i < max_code; i++) {
        if (is_valid(i)) {
            codes[count++] = i;
            if (count == n) {
                return;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &b, &d);
    generate_codes();

    for (int i = 0; i < n; i++) {
        printf("%d", codes[i]);
        if ((i + 1) % 10 == 0 || i == n - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }

    return 0;
}
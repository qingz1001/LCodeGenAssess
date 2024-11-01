#include <stdio.h>
#include <stdlib.h>

int hammingDistance(int a, int b, int b_bits) {
    int distance = 0;
    for (int i = 0; i < b_bits; i++) {
        if ((a & (1 << i)) != (b & (1 << i))) {
            distance++;
        }
    }
    return distance;
}

int main() {
    int n, b, d;
    scanf("%d %d %d", &n, &b, &d);

    int *codes = (int *)malloc(n * sizeof(int));
    int count = 0;
    int current = 0;

    while (count < n) {
        int valid = 1;
        for (int i = 0; i < count; i++) {
            if (hammingDistance(current, codes[i], b) < d) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            codes[count++] = current;
        }
        current++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d", codes[i]);
        if ((i + 1) % 10 == 0 || i == n - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }

    free(codes);
    return 0;
}
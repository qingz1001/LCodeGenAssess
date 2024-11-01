#include <stdio.h>

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    int i, j, remainder = 1;
    for (i = 0; i < k; i++) {
        for (j = 0; j < i + 1; j++) {
            printf("%d", j);
            remainder = (remainder * 10 + j) % m;
        }
        if (remainder == 0) {
            break;
        }
    }

    if (remainder != 0) {
        printf("No valid number found");
    }

    return 0;
}
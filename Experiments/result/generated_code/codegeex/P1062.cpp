#include <stdio.h>

int main() {
    int k, N;
    scanf("%d %d", &k, &N);

    int result = 0;
    int power = 1;

    for (int i = 0; i < N; i++) {
        result += power;
        power *= k;
    }

    printf("%d\n", result);

    return 0;
}
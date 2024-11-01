#include <stdio.h>
#include <math.h>

int main() {
    int k, N;
    scanf("%d %d", &k, &N);

    int result = 0;
    int power = 1;

    while (N > 0) {
        if (N % 2 == 1) {
            result += power;
        }
        power *= k;
        N /= 2;
    }

    printf("%d\n", result);
    return 0;
}
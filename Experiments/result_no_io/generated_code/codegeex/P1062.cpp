#include <stdio.h>
#include <math.h>

int main() {
    int k, N;
    scanf("%d %d", &k, &N);

    int result = 0;
    for (int i = 0; i < N; i++) {
        int power = 1;
        for (int j = 0; j < i; j++) {
            power *= k;
        }
        result += power;
    }

    printf("%d\n", result);
    return 0;
}
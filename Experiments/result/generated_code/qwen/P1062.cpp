#include <stdio.h>
#include <math.h>

int main() {
    int k, N;
    scanf("%d %d", &k, &N);

    int count = 0;
    for (int i = 0; i <= 15; i++) {
        for (int j = 0; j < (1 << i); j++) {
            int sum = 0;
            for (int m = 0; m < i; m++) {
                if (j & (1 << m)) {
                    sum += pow(k, m);
                }
            }
            count++;
            if (count == N) {
                printf("%d\n", sum);
                return 0;
            }
        }
    }

    return 0;
}
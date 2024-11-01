#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        long long A;
        scanf("%lld", &A);
        long long k = (long long)(sqrt(2.0 * A) - 1) / 2;
        if ((k + 1) * (k + 2) / 2 == A) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
    return 0;
}
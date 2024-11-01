#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        long long A;
        scanf("%lld", &A);
        if ((A - 1) % 3 == 2) {
            printf("0\n");
        } else {
            printf("1\n");
        }
    }
    return 0;
}
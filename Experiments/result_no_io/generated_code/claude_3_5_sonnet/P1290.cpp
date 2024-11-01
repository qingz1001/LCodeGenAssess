#include <stdio.h>

int main() {
    int C;
    scanf("%d", &C);

    while (C--) {
        long long M, N;
        scanf("%lld %lld", &M, &N);

        int turn = 0; // 0 for Stan, 1 for Ollie

        while (M != 0 && N != 0) {
            if (M < N) {
                long long temp = M;
                M = N;
                N = temp;
            }

            if (M % N == 0) {
                break;
            }

            M %= N;
            turn = 1 - turn;
        }

        if (turn == 0) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }
    }

    return 0;
}
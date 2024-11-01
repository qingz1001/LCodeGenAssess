#include <stdio.h>

int euclidean_game(int M, int N) {
    int turn = 0; // 0 for Stan, 1 for Ollie
    while (M != 0 && N != 0) {
        if (M < N) {
            int temp = M;
            M = N;
            N = temp;
        }
        if (M % N == 0) {
            break;
        }
        if (M / N > 1) {
            break;
        }
        M -= N;
        turn = 1 - turn;
    }
    return turn;
}

int main() {
    int C;
    scanf("%d", &C);
    for (int i = 0; i < C; i++) {
        int M, N;
        scanf("%d %d", &M, &N);
        if (euclidean_game(M, N) == 0) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }
    }
    return 0;
}
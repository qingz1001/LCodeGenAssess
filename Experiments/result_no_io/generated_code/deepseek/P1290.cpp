#include <stdio.h>

int euclidean_game(int M, int N) {
    if (M < N) {
        int temp = M;
        M = N;
        N = temp;
    }
    while (N != 0) {
        if (M / N > 1) {
            return 1; // Stan wins
        }
        int temp = M % N;
        M = N;
        N = temp;
    }
    return 0; // Ollie wins
}

int main() {
    int C;
    scanf("%d", &C);
    for (int i = 0; i < C; i++) {
        int M, N;
        scanf("%d %d", &M, &N);
        if (euclidean_game(M, N)) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }
    }
    return 0;
}
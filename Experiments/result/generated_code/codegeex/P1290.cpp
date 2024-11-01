#include <stdio.h>

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        int M, N;
        scanf("%d%d", &M, &N);
        if (M > N) {
            M = M - N;
        } else if (M < N) {
            N = N - M;
        } else {
            printf("Stan wins\n");
            continue;
        }
        if (M % N == 0) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }
    }
    return 0;
}
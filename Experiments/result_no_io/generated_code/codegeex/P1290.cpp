#include <stdio.h>

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        int M, N;
        scanf("%d%d", &M, &N);
        while (M > 0 && N > 0) {
            if (M > N) {
                M %= N;
            } else {
                N %= M;
            }
        }
        if (M == 0) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }
    }
    return 0;
}
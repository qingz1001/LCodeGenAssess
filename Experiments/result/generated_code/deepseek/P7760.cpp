#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, X;
    scanf("%d", &N);
    scanf("%d", &X);

    int total_value = 0;

    for (int i = 0; i < N; i++) {
        int P1, P2, P3 = 0;
        scanf("%d %d", &P1, &P2);
        if (abs(P1 - P2) > X) {
            scanf("%d", &P3);
        }

        if (abs(P1 - P2) <= X) {
            total_value += (P1 > P2) ? P1 : P2;
        } else {
            total_value += P3;
        }
    }

    printf("%d\n", total_value);
    return 0;
}
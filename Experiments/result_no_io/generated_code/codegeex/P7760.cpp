#include <stdio.h>

int main() {
    int N, X;
    scanf("%d %d", &N, &X);
    int total_value = 0;

    for (int i = 0; i < N; i++) {
        int P1, P2, P3 = 0;
        scanf("%d %d", &P1, &P2);

        if (P1 > P2) {
            if (P1 - P2 <= X) {
                total_value += P1;
            } else {
                total_value += P2;
            }
        } else {
            if (P2 - P1 <= X) {
                total_value += P2;
            } else {
                total_value += P1;
            }
        }

        int has_P3 = scanf("%d", &P3);
        if (has_P3 == 1) {
            if (P1 > P2) {
                if (P1 - P2 > X) {
                    total_value += P3;
                }
            } else {
                if (P2 - P1 > X) {
                    total_value += P3;
                }
            }
        }
    }

    printf("%d\n", total_value);
    return 0;
}
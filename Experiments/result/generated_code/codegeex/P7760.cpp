#include <stdio.h>

int main() {
    int N, X, P1, P2, P3, total_value = 0;
    scanf("%d %d", &N, &X);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &P1, &P2);
        if (P1 - P2 <= X) {
            total_value += P1;
        } else {
            scanf("%d", &P3);
            total_value += P3;
        }
    }

    printf("%d\n", total_value);
    return 0;
}
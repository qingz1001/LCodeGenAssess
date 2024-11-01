#include <stdio.h>

int main() {
    int T, m, K;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &m, &K);
        if ((K & (K - 1)) == 0) {
            printf("-1\n");
        } else {
            printf("%d\n", m + 1);
        }
    }
    return 0;
}
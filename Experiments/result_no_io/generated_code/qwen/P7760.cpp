#include <stdio.h>

int main() {
    int N, X;
    scanf("%d %d", &N, &X);

    int total_value = 0;

    for (int i = 0; i < N; i++) {
        int p1, p2, p3 = 0;
        if (scanf("%d %d", &p1, &p2) == 2) {
            // Case where there are only two values
            if (p1 - p2 <= X) {
                total_value += (p1 > p2 ? p1 : p2);
            } else {
                total_value += p2;
            }
        } else if (scanf("%d %d %d", &p1, &p2, &p3) == 3) {
            // Case where there are three values
            if (p1 - p2 <= X) {
                total_value += (p1 > p2 ? p1 : p2);
            } else {
                total_value += p3;
            }
        }
    }

    printf("%d\n", total_value);

    return 0;
}
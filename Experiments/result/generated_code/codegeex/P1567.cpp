#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int max_days = 1;
    int current_days = 1;

    for (int i = 1; i < N; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (b > a) {
            current_days++;
            if (current_days > max_days) {
                max_days = current_days;
            }
        } else {
            current_days = 1;
        }
    }

    printf("%d\n", max_days);
    return 0;
}
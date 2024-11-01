#include <stdio.h>

#define MAX_N 1000000

int main() {
    int N;
    long long temperatures[MAX_N];
    int max_days = 1;
    int current_days = 1;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%lld", &temperatures[i]);
    }

    for (int i = 1; i < N; i++) {
        if (temperatures[i] > temperatures[i-1]) {
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
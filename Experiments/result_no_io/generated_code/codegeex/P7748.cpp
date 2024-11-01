#include <stdio.h>

int main() {
    int K, N;
    scanf("%d%d", &K, &N);

    int total_time = 0;
    for (int i = 0; i < N; i++) {
        int T;
        char result;
        scanf("%d %c", &T, &result);

        total_time += T;

        if (total_time >= 210) {
            printf("%d\n", K);
            return 0;
        }

        if (result == 'T') {
            K = (K % 8) + 1;
        }
    }

    return 0;
}
#include <stdio.h>

int main() {
    int K, N;
    scanf("%d %d", &K, &N);

    int current_time = 0;
    for (int i = 0; i < N; i++) {
        int T;
        char response;
        scanf("%d %c", &T, &response);

        current_time += T;
        if (current_time >= 210) {
            printf("%d\n", K);
            return 0;
        }

        if (response == 'T') {
            K = (K % 8) + 1;
        }
    }

    printf("%d\n", K);
    return 0;
}
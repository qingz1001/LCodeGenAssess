#include <stdio.h>

int main() {
    int K, N;
    scanf("%d", &K);
    scanf("%d", &N);

    int total_time = 0;
    int current_player = K;

    for (int i = 0; i < N; i++) {
        int T;
        char result;
        scanf("%d %c", &T, &result);

        total_time += T;

        if (total_time >= 210) {
            printf("%d\n", current_player);
            return 0;
        }

        if (result == 'T') {
            current_player = (current_player % 8) + 1;
        }
    }

    printf("%d\n", current_player);
    return 0;
}
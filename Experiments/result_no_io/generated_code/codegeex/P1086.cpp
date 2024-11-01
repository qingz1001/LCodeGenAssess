#include <stdio.h>

int main() {
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);

    int field[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
        }
    }

    int max_pos = -1;
    int max_val = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (field[i][j] > max_val) {
                max_val = field[i][j];
                max_pos = i * N + j;
            }
        }
    }

    int total_time = 0;
    int total_peanuts = 0;
    int last_pos = -1;

    while (max_pos != -1 && total_time + max_val * 2 + M - max_pos <= K) {
        if (last_pos == -1) {
            total_time += M - max_pos;
        } else {
            int x1 = max_pos / N;
            int y1 = max_pos % N;
            int x2 = last_pos / N;
            int y2 = last_pos % N;
            total_time += abs(x1 - x2) + abs(y1 - y2) + 1;
        }
        total_peanuts += max_val;
        last_pos = max_pos;

        max_val = 0;
        max_pos = -1;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] > max_val) {
                    max_val = field[i][j];
                    max_pos = i * N + j;
                }
            }
        }
    }

    printf("%d\n", total_peanuts);
    return 0;
}
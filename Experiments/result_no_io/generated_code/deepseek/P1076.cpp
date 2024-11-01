#include <stdio.h>

#define MOD 20123

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int rooms[N][M];
    int stairs[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &stairs[i][j], &rooms[i][j]);
        }
    }

    int start;
    scanf("%d", &start);

    int key = 0;

    for (int i = 0; i < N; i++) {
        int current = start;
        int steps = rooms[i][current];
        key = (key + steps) % MOD;

        int count = 0;
        while (count < steps) {
            if (stairs[i][current] == 1) {
                count++;
            }
            current = (current + 1) % M;
        }

        start = current - 1;
        if (start < 0) start += M;
    }

    printf("%d\n", key);

    return 0;
}
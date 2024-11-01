#include <stdio.h>

#define MOD 20123

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int hasStairs[N][M];
    int sign[N][M];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%d %d", &hasStairs[i][j], &sign[i][j]);
        }
    }

    int startRoom;
    scanf("%d", &startRoom);

    int keySum = 0;

    for (int i = 0; i < N; ++i) {
        int currentRoom = startRoom;
        int steps = sign[i][currentRoom];
        while (!hasStairs[i][currentRoom]) {
            currentRoom = (currentRoom + 1) % M;
            steps--;
            if (steps == 0) {
                steps = sign[i][currentRoom];
            }
        }
        keySum = (keySum + sign[i][currentRoom]) % MOD;
    }

    printf("%d\n", keySum);

    return 0;
}
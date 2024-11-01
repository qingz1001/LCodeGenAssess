#include <stdio.h>

#define MOD 20123

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int rooms[N][M][2];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &rooms[i][j][0], &rooms[i][j][1]);
        }
    }

    int start_room;
    scanf("%d", &start_room);

    int key = 0;
    for (int i = 0; i < N; i++) {
        int current_room = start_room;
        int count = 0;
        int steps = rooms[i][current_room][1];

        while (count < steps) {
            if (rooms[i][current_room][0] == 1) {
                count++;
            }
            if (count < steps) {
                current_room = (current_room + 1) % M;
            }
        }

        key = (key + rooms[i][current_room][1]) % MOD;
        start_room = current_room;
    }

    printf("%d\n", key);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MOD 20123

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int **rooms = (int **)malloc(N * sizeof(int *));
    int **indicators = (int **)malloc(N * sizeof(int *));
    int *stairs_count = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        rooms[i] = (int *)malloc(M * sizeof(int));
        indicators[i] = (int *)malloc(M * sizeof(int));
        stairs_count[i] = 0;
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &rooms[i][j], &indicators[i][j]);
            if (rooms[i][j] == 1) {
                stairs_count[i]++;
            }
        }
    }

    int start_room;
    scanf("%d", &start_room);

    int key = 0;
    int current_room = start_room;

    for (int i = 0; i < N; i++) {
        int steps = indicators[i][current_room];
        key = (key + steps) % MOD;

        int count = 0;
        while (count < steps) {
            if (rooms[i][current_room] == 1) {
                count++;
            }
            current_room = (current_room + 1) % M;
        }

        // Move back one step to the correct room
        while (rooms[i][current_room] == 0) {
            current_room = (current_room + 1) % M;
        }
    }

    printf("%d\n", key);

    for (int i = 0; i < N; i++) {
        free(rooms[i]);
        free(indicators[i]);
    }
    free(rooms);
    free(indicators);
    free(stairs_count);

    return 0;
}
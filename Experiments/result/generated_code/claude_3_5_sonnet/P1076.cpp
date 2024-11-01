#include <stdio.h>
#define MAX_N 10000
#define MAX_M 100
#define MOD 20123

int N, M;
int has_stairs[MAX_N][MAX_M];
int indicator[MAX_N][MAX_M];

int find_next_room(int floor, int current_room, int steps) {
    int count = 0;
    while (count < steps) {
        if (has_stairs[floor][current_room]) {
            count++;
        }
        if (count == steps) break;
        current_room = (current_room + 1) % M;
    }
    return current_room;
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &has_stairs[i][j], &indicator[i][j]);
        }
    }

    int start_room;
    scanf("%d", &start_room);

    int sum = 0;
    int current_room = start_room;

    for (int floor = 0; floor < N; floor++) {
        sum = (sum + indicator[floor][current_room]) % MOD;
        int next_room = find_next_room(floor, current_room, indicator[floor][current_room]);
        current_room = next_room;
    }

    printf("%d\n", sum);

    return 0;
}
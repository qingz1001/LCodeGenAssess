#include <stdio.h>
#define MAX_N 10000
#define MAX_M 100
#define MOD 20123

int N, M;
int hasStairs[MAX_N][MAX_M];
int indicator[MAX_N][MAX_M];

int findNextStair(int floor, int start) {
    int count = indicator[floor][start];
    int current = start;
    while (count > 0) {
        if (hasStairs[floor][current]) {
            count--;
        }
        if (count == 0) break;
        current = (current + 1) % M;
    }
    return current;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &hasStairs[i][j], &indicator[i][j]);
        }
    }
    
    int startRoom;
    scanf("%d", &startRoom);
    
    int sum = 0;
    int currentRoom = startRoom;
    
    for (int floor = 0; floor < N; floor++) {
        sum = (sum + indicator[floor][currentRoom]) % MOD;
        currentRoom = findNextStair(floor, currentRoom);
    }
    
    printf("%d\n", sum);
    
    return 0;
}
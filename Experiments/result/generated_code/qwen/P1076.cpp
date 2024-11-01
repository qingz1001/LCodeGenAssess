#include <stdio.h>

#define MOD 20123

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int floors[N][M][2];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &floors[i][j][0], &floors[i][j][1]);
        }
    }
    
    int startRoom;
    scanf("%d", &startRoom);
    
    long long key = 0;
    for (int i = 0; i < N; i++) {
        int currentRoom = startRoom;
        while (floors[i][currentRoom][0]) {
            currentRoom = (currentRoom + floors[i][currentRoom][1]) % M;
        }
        key = (key + floors[i][currentRoom][1]) % MOD;
    }
    
    printf("%lld\n", key);
    
    return 0;
}
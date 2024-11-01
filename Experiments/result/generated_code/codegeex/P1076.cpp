#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int rooms[N][M][2]; // rooms[i][j][0] 表示是否有楼梯，rooms[i][j][1] 表示指示牌上的数字
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d %d", &rooms[i][j][0], &rooms[i][j][1]);
        }
    }
    
    int startRoom;
    scanf("%d", &startRoom);
    
    int sum = 0;
    int currentFloor = 0;
    int currentRoom = startRoom;
    
    while (currentFloor < N) {
        sum = (sum + rooms[currentFloor][currentRoom][1]) % 20123;
        
        int count = 0;
        int nextRoom = currentRoom;
        
        // 统计当前楼层有楼梯的房间数量
        for (int j = 0; j < M; j++) {
            if (rooms[currentFloor][j][0] == 1) {
                count++;
            }
        }
        
        // 根据指示牌上的数字找到下一个有楼梯的房间
        for (int j = 0; j < rooms[currentFloor][currentRoom][1]; j++) {
            do {
                nextRoom = (nextRoom + 1) % M;
            } while (rooms[currentFloor][nextRoom][0] == 0);
        }
        
        // 更新当前楼层和房间
        currentFloor++;
        currentRoom = nextRoom;
    }
    
    printf("%d\n", sum);
    return 0;
}
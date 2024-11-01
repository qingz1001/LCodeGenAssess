#include <stdio.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 50

int n, m;
int castle[MAX_N][MAX_M];
int room[MAX_N][MAX_M];
int roomSize[MAX_N * MAX_M];
int roomCount = 0;
int maxRoomSize = 0;
int maxCombinedSize = 0;
int removeWallRow, removeWallCol;
char removeWallDir;

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

void dfs(int x, int y, int id) {
    if (x < 0 || x >= n || y < 0 || y >= m || room[x][y] != 0) return;
    
    room[x][y] = id;
    roomSize[id]++;
    
    for (int i = 0; i < 4; i++) {
        if ((castle[x][y] & (1 << i)) == 0) {
            dfs(x + dx[i], y + dy[i], id);
        }
    }
}

void findRooms() {
    memset(room, 0, sizeof(room));
    memset(roomSize, 0, sizeof(roomSize));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (room[i][j] == 0) {
                roomCount++;
                dfs(i, j, roomCount);
                if (roomSize[roomCount] > maxRoomSize) {
                    maxRoomSize = roomSize[roomCount];
                }
            }
        }
    }
}

void findMaxCombinedRoom() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Check east wall
            if (j < m - 1 && room[i][j] != room[i][j+1]) {
                int combinedSize = roomSize[room[i][j]] + roomSize[room[i][j+1]];
                if (combinedSize > maxCombinedSize) {
                    maxCombinedSize = combinedSize;
                    removeWallRow = i + 1;
                    removeWallCol = j + 1;
                    removeWallDir = 'E';
                }
            }
            // Check north wall
            if (i > 0 && room[i][j] != room[i-1][j]) {
                int combinedSize = roomSize[room[i][j]] + roomSize[room[i-1][j]];
                if (combinedSize > maxCombinedSize || 
                    (combinedSize == maxCombinedSize && 
                     (j + 1 < removeWallCol || (j + 1 == removeWallCol && i + 1 > removeWallRow)))) {
                    maxCombinedSize = combinedSize;
                    removeWallRow = i;
                    removeWallCol = j + 1;
                    removeWallDir = 'N';
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &castle[i][j]);
        }
    }
    
    findRooms();
    findMaxCombinedRoom();
    
    printf("%d\n", roomCount);
    printf("%d\n", maxRoomSize);
    printf("%d\n", maxCombinedSize);
    printf("%d %d %c\n", removeWallRow, removeWallCol, removeWallDir);
    
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAXN 50
#define MAXM 50

int n, m;
int castle[MAXN][MAXM];
int room[MAXN][MAXM];
int roomSize[MAXN*MAXM];
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

int dfs(int x, int y, int id) {
    if (x < 0 || x >= n || y < 0 || y >= m || room[x][y]) return 0;
    room[x][y] = id;
    int size = 1;
    for (int i = 0; i < 4; i++) {
        if (!(castle[x][y] & (1 << i))) {
            size += dfs(x + dx[i], y + dy[i], id);
        }
    }
    return size;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &castle[i][j]);
        }
    }
    
    int roomCount = 0;
    int maxRoomSize = 0;
    memset(room, 0, sizeof(room));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!room[i][j]) {
                roomSize[++roomCount] = dfs(i, j, roomCount);
                if (roomSize[roomCount] > maxRoomSize) {
                    maxRoomSize = roomSize[roomCount];
                }
            }
        }
    }
    
    int maxCombinedSize = 0;
    int wallX = 0, wallY = 0;
    char wallDir = 'N';
    
    for (int j = 0; j < m; j++) {
        for (int i = n-1; i >= 0; i--) {
            if (i > 0 && room[i][j] != room[i-1][j]) {
                int newSize = roomSize[room[i][j]] + roomSize[room[i-1][j]];
                if (newSize > maxCombinedSize) {
                    maxCombinedSize = newSize;
                    wallX = i;
                    wallY = j+1;
                    wallDir = 'N';
                }
            }
            if (j < m-1 && room[i][j] != room[i][j+1]) {
                int newSize = roomSize[room[i][j]] + roomSize[room[i][j+1]];
                if (newSize > maxCombinedSize) {
                    maxCombinedSize = newSize;
                    wallX = i+1;
                    wallY = j+1;
                    wallDir = 'E';
                }
            }
        }
    }
    
    printf("%d\n", roomCount);
    printf("%d\n", maxRoomSize);
    printf("%d\n", maxCombinedSize);
    printf("%d %d %c\n", wallX, wallY, wallDir);
    
    return 0;
}
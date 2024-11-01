#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <limits.h>

using namespace std;

#define MAXN 40
#define MAXM 26

int R, C;
int king_x, king_y;
int knight_x[MAXN], knight_y[MAXN];
int knight_cnt = 0;
int visited[MAXN][MAXM][MAXN][MAXM];
int dist[MAXN][MAXM][MAXN][MAXM];
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct Node {
    int x, y, step;
};

void bfs(int start_x, int start_y) {
    queue<Node> q;
    memset(visited, 0, sizeof(visited));
    memset(dist, 0x3f, sizeof(dist));
    visited[start_x][start_y] = 1;
    dist[start_x][start_y] = 0;
    q.push({start_x, start_y, 0});
    
    while (!q.empty()) {
        Node current = q.front();
        q.pop();
        
        for (int i = 0; i < 8; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                dist[nx][ny] = current.step + 1;
                q.push({nx, ny, current.step + 1});
            }
        }
    }
}

int main() {
    scanf("%d%d", &R, &C);
    char king_col;
    scanf(" %c%d", &king_col, &king_y);
    king_x = king_col - 'A';
    while (scanf(" %c%d", &king_col, &knight_y) == 2) {
        knight_x[knight_cnt] = king_col - 'A';
        knight_cnt++;
    }
    
    bfs(king_x, king_y);
    
    int min_steps = INT_MAX;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int total_steps = dist[i][j][king_x][king_y];
            for (int k = 0; k < knight_cnt; k++) {
                if (dist[i][j][knight_x[k]][knight_y[k]] == INT_MAX) {
                    total_steps = INT_MAX;
                    break;
                }
                total_steps += dist[i][j][knight_x[k]][knight_y[k]];
            }
            if (total_steps < min_steps) {
                min_steps = total_steps;
            }
        }
    }
    
    printf("%d\n", min_steps);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_R 40
#define MAX_C 26

typedef struct {
    int r, c;
} Position;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int abs(int x) {
    return (x < 0) ? -x : x;
}

int knight_moves[8][2] = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

int bfs(Position start, Position end, int R, int C, char board[MAX_R][MAX_C]) {
    if (start.r == end.r && start.c == end.c) return 0;

    int dist[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            dist[i][j] = -1;
        }
    }

    queue<Position> q;
    q.push(start);
    dist[start.r][start.c] = 0;

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        for (int k = 0; k < 8; k++) {
            int new_r = current.r + knight_moves[k][0];
            int new_c = current.c + knight_moves[k][1];

            if (new_r >= 0 && new_r < R && new_c >= 0 && new_c < C && board[new_r][new_c] != 'K' && dist[new_r][new_c] == -1) {
                dist[new_r][new_c] = dist[current.r][current.c] + 1;
                if (new_r == end.r && new_c == end.c) return dist[new_r][new_c];
                q.push({new_r, new_c});
            }
        }
    }

    return -1;
}

int main() {
    int R, C;
    scanf("%d %d", &R, &C);

    char board[MAX_R][MAX_C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf(" %c", &board[i][j]);
        }
    }

    Position king, knights[MAX_C * MAX_R];
    int knight_count = 0;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == 'K') {
                king.r = i;
                king.c = j;
            } else if (board[i][j] >= '1' && board[i][j] <= '8') {
                knights[knight_count].r = i;
                knights[knight_count].c = j;
                knight_count++;
            }
        }
    }

    int min_steps = INT_MAX;

    for (int i = 0; i < knight_count; i++) {
        Position meeting_point = knights[i];
        int steps = bfs(king, meeting_point, R, C, board);
        if (steps != -1) {
            steps += bfs(meeting_point, knights[i], R, C, board);
            min_steps = min(min_steps, steps);
        }
    }

    printf("%d\n", min_steps);

    return 0;
}
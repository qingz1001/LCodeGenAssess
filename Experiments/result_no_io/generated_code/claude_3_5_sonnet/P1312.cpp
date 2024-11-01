#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 5
#define ROWS 7
#define COLS 5

int n;
int board[ROWS][COLS];
int moves[MAX_N][3];
int move_count = 0;

bool dfs(int depth);
bool move(int x, int y, int dir);
void undo_move(int x, int y, int dir);
void eliminate();
bool is_cleared();

int main() {
    scanf("%d", &n);
    
    for (int j = 0; j < COLS; j++) {
        int i = 0;
        while (true) {
            int color;
            scanf("%d", &color);
            if (color == 0) break;
            board[i++][j] = color;
        }
    }
    
    if (dfs(0)) {
        for (int i = 0; i < n; i++) {
            printf("%d %d %d\n", moves[i][0], moves[i][1], moves[i][2]);
        }
    } else {
        printf("-1\n");
    }
    
    return 0;
}

bool dfs(int depth) {
    if (depth == n) {
        return is_cleared();
    }
    
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            if (board[x][y] == 0) continue;
            
            for (int dir = 1; dir >= -1; dir -= 2) {
                if (move(x, y, dir)) {
                    moves[depth][0] = x;
                    moves[depth][1] = y;
                    moves[depth][2] = dir;
                    
                    if (dfs(depth + 1)) {
                        return true;
                    }
                    
                    undo_move(x, y, dir);
                }
            }
        }
    }
    
    return false;
}

bool move(int x, int y, int dir) {
    int ny = y + dir;
    if (ny < 0 || ny >= COLS) return false;
    
    if (board[x][ny] == 0) {
        for (int i = x; i < ROWS - 1 && board[i][y] != 0; i++) {
            board[i][ny] = board[i+1][y];
            board[i+1][y] = 0;
        }
    } else {
        int temp = board[x][y];
        board[x][y] = board[x][ny];
        board[x][ny] = temp;
    }
    
    eliminate();
    return true;
}

void undo_move(int x, int y, int dir) {
    int ny = y + dir;
    
    if (board[x][ny] == 0) {
        for (int i = ROWS - 1; i > x; i--) {
            board[i][y] = board[i-1][y];
        }
        board[x][y] = board[x][ny];
        board[x][ny] = 0;
    } else {
        int temp = board[x][y];
        board[x][y] = board[x][ny];
        board[x][ny] = temp;
    }
}

void eliminate() {
    bool eliminated;
    do {
        eliminated = false;
        
        int temp[ROWS][COLS];
        memcpy(temp, board, sizeof(board));
        
        for (int x = 0; x < ROWS; x++) {
            for (int y = 0; y < COLS; y++) {
                if (board[x][y] == 0) continue;
                
                int color = board[x][y];
                int count_h = 1, count_v = 1;
                
                for (int i = y + 1; i < COLS && board[x][i] == color; i++) count_h++;
                for (int i = y - 1; i >= 0 && board[x][i] == color; i--) count_h++;
                for (int i = x + 1; i < ROWS && board[i][y] == color; i++) count_v++;
                for (int i = x - 1; i >= 0 && board[i][y] == color; i--) count_v++;
                
                if (count_h >= 3 || count_v >= 3) {
                    eliminated = true;
                    if (count_h >= 3) {
                        for (int i = y - count_h + 1; i <= y + count_h - 1; i++) {
                            if (i >= 0 && i < COLS) temp[x][i] = 0;
                        }
                    }
                    if (count_v >= 3) {
                        for (int i = x - count_v + 1; i <= x + count_v - 1; i++) {
                            if (i >= 0 && i < ROWS) temp[i][y] = 0;
                        }
                    }
                }
            }
        }
        
        memcpy(board, temp, sizeof(board));
        
        for (int y = 0; y < COLS; y++) {
            int write = 0;
            for (int x = 0; x < ROWS; x++) {
                if (board[x][y] != 0) {
                    board[write++][y] = board[x][y];
                }
            }
            while (write < ROWS) {
                board[write++][y] = 0;
            }
        }
    } while (eliminated);
}

bool is_cleared() {
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            if (board[x][y] != 0) return false;
        }
    }
    return true;
}
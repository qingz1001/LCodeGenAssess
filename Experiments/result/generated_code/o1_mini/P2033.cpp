#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define MAX_CMD 20

int main(){
    char board[BOARD_SIZE][BOARD_SIZE];
    int i, j;
    int x, y;
    int dir; // 0: up, 1: right, 2: down, 3: left
    // Read the board and find initial position and direction
    for(i=0;i<BOARD_SIZE;i++){
        scanf("%s", board[i]);
        for(j=0;j<BOARD_SIZE;j++){
            if(board[i][j]=='^' || board[i][j]=='v' || board[i][j]=='<' || board[i][j]=='>'){
                x = i;
                y = j;
                switch(board[i][j]){
                    case '^': dir = 0; break;
                    case '>': dir = 1; break;
                    case 'v': dir = 2; break;
                    case '<': dir = 3; break;
                }
                board[i][j] = '.';
            }
        }
    }
    // Directions: up, right, down, left
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    char cmd[MAX_CMD];
    while(1){
        scanf("%s", cmd);
        if(strcmp(cmd, "#")==0) break;
        if(strcmp(cmd, "move")==0){
            int n;
            scanf("%d", &n);
            for(int step=0; step<n; step++){
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if(nx <0 || nx >= BOARD_SIZE || ny <0 || ny >= BOARD_SIZE){
                    break;
                }
                if(board[nx][ny] == '.'){
                    x = nx;
                    y = ny;
                }
                else{
                    int push_x = nx + dx[dir];
                    int push_y = ny + dy[dir];
                    if(push_x <0 || push_x >= BOARD_SIZE || push_y <0 || push_y >= BOARD_SIZE){
                        break;
                    }
                    if(board[push_x][push_y] != '.'){
                        break;
                    }
                    board[push_x][push_y] = board[nx][ny];
                    board[nx][ny] = '.';
                    x = nx;
                    y = ny;
                }
            }
        }
        else if(strcmp(cmd, "turn")==0){
            char turn_dir[10];
            scanf("%s", turn_dir);
            if(strcmp(turn_dir, "left")==0){
                dir = (dir + 3) % 4;
            }
            else if(strcmp(turn_dir, "right")==0){
                dir = (dir + 1) % 4;
            }
            else if(strcmp(turn_dir, "back")==0){
                dir = (dir + 2) % 4;
            }
        }
        else{
            // Ignore invalid commands
            fgets(cmd, MAX_CMD, stdin);
        }
    }
    // Set the current position with direction symbol
    char symbol;
    switch(dir){
        case 0: symbol = '^'; break;
        case 1: symbol = '>'; break;
        case 2: symbol = 'v'; break;
        case 3: symbol = '<'; break;
    }
    board[x][y] = symbol;
    // Print the board
    for(i=0;i<BOARD_SIZE;i++){
        for(j=0;j<BOARD_SIZE;j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char board[8][8];
    int x=0, y=0, dir=0;
    // Directions: 0 - up (^), 1 - right (>), 2 - down (v), 3 - left (<)
    int dx_move[4] = {-1, 0, 1, 0};
    int dy_move[4] = {0, 1, 0, -1};
    // Read initial board
    for(int i=0;i<8;i++){
        char line[10];
        fgets(line, sizeof(line), stdin);
        for(int j=0; j<8; j++){
            board[i][j] = line[j];
            if(line[j] == '^'){
                x = i;
                y = j;
                dir = 0;
                board[i][j] = '.';
            }
            else if(line[j] == '>'){
                x = i;
                y = j;
                dir = 1;
                board[i][j] = '.';
            }
            else if(line[j] == 'v'){
                x = i;
                y = j;
                dir = 2;
                board[i][j] = '.';
            }
            else if(line[j] == '<'){
                x = i;
                y = j;
                dir = 3;
                board[i][j] = '.';
            }
        }
    }
    // Read operations
    char op_line[20];
    while(fgets(op_line, sizeof(op_line), stdin)){
        // Remove trailing newline
        op_line[strcspn(op_line, "\n")] = 0;
        if(strcmp(op_line, "#") == 0){
            break;
        }
        if(strncmp(op_line, "move ", 5) ==0){
            int n = atoi(op_line + 5);
            for(int step=0; step<n; step++){
                int tx = x + dx_move[dir];
                int ty = y + dy_move[dir];
                if(tx <0 || tx >=8 || ty <0 || ty >=8){
                    break;
                }
                if(board[tx][ty] == '.'){
                    x = tx;
                    y = ty;
                }
                else{
                    int px = tx + dx_move[dir];
                    int py = ty + dy_move[dir];
                    if(px <0 || px >=8 || py <0 || py >=8 || board[px][py] != '.'){
                        break;
                    }
                    board[px][py] = board[tx][ty];
                    board[tx][ty] = '.';
                    x = tx;
                    y = ty;
                }
            }
        }
        else if(strcmp(op_line, "turn left") ==0){
            dir = (dir +3)%4;
        }
        else if(strcmp(op_line, "turn right") ==0){
            dir = (dir +1)%4;
        }
        else if(strcmp(op_line, "turn back") ==0){
            dir = (dir +2)%4;
        }
    }
    // Assign direction symbol
    char dir_char;
    if(dir ==0){
        dir_char='^';
    }
    else if(dir ==1){
        dir_char='>';
    }
    else if(dir ==2){
        dir_char='v';
    }
    else{
        dir_char='<';
    }
    board[x][y] = dir_char;
    // Print board
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX 1000

char grid[MAX][MAX + 1];
int visited_cells[MAX][MAX];
int R, C;

int main(){
    scanf("%d %d", &R, &C);
    for(int i=0;i<R;i++){
        scanf("%s", grid[i]);
    }
    memset(visited_cells, 0, sizeof(visited_cells));
    int ship_count = 0;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(grid[i][j] == '#' && !visited_cells[i][j]){
                // Determine the size of the square
                int size = 1;
                while(1){
                    if(i + size >= R || j + size >= C)
                        break;
                    int flag = 1;
                    for(int k=0;k<=size;k++){
                        if(grid[i + size][j + k] != '#' || grid[i + k][j + size] != '#'){
                            flag = 0;
                            break;
                        }
                    }
                    if(flag)
                        size++;
                    else
                        break;
                }
                // Verify all cells in the square are '#'
                int valid = 1;
                for(int a=i; a<i+size && valid; a++){
                    for(int b=j; b<j+size && valid; b++){
                        if(grid[a][b] != '#'){
                            valid = 0;
                        }
                    }
                }
                if(!valid){
                    printf("Bad placement.\n");
                    return 0;
                }
                // Check perimeter
                // Above
                if(i > 0){
                    for(int b=j; b<j+size; b++){
                        if(grid[i-1][b] == '#'){
                            printf("Bad placement.\n");
                            return 0;
                        }
                    }
                }
                // Below
                if(i + size < R){
                    for(int b=j; b<j+size; b++){
                        if(grid[i + size][b] == '#'){
                            printf("Bad placement.\n");
                            return 0;
                        }
                    }
                }
                // Left
                if(j > 0){
                    for(int a=i; a<i+size; a++){
                        if(grid[a][j-1] == '#'){
                            printf("Bad placement.\n");
                            return 0;
                        }
                    }
                }
                // Right
                if(j + size < C){
                    for(int a=i; a<i+size; a++){
                        if(grid[a][j + size] == '#'){
                            printf("Bad placement.\n");
                            return 0;
                        }
                    }
                }
                // Mark visited
                for(int a=i; a<i+size; a++){
                    for(int b=j; b<j+size; b++){
                        visited_cells[a][b] = 1;
                    }
                }
                ship_count++;
            }
        }
    }
    printf("There are %d ships.\n", ship_count);
    return 0;
}
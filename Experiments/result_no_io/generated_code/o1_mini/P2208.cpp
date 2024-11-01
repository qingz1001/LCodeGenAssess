#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define MAX_QUEUE (500*500*2)
#define INF 1000000000

typedef struct {
    int x;
    int y;
    int g;
} State;

int main(){
    int N,M;
    scanf("%d %d", &N, &M);
    char grid[MAX+1][MAX+1];
    int start_x, start_y, end_x, end_y;
    for(int i=0;i<N;i++){
        scanf("%s", grid[i]);
        for(int j=0;j<M;j++) {
            if(grid[i][j]=='C'){
                start_x = i;
                start_y = j;
            }
            if(grid[i][j]=='D'){
                end_x = i;
                end_y = j;
            }
        }
    }
    int visited[MAX][MAX][2];
    memset(visited, -1, sizeof(visited));
    State queue[MAX_QUEUE];
    int head=0, tail=0;
    // Initialize
    queue[tail++] = (State){start_x, start_y, 0};
    visited[start_x][start_y][0] = 0;
    // Directions
    int dx[2] = {1, -1};
    int dy[2] = {0, 0};
    while(head < tail){
        State current = queue[head++];
        if(current.x == end_x && current.y == end_y){
            printf("%d", visited[current.x][current.y][current.g]);
            return 0;
        }
        int g = current.g;
        int under = current.x + dx[g];
        // Fall
        if(under < 0 || under >= N || grid[under][current.y] == '#'){
            // Can move
            for(int dir=-1; dir<=1; dir+=2){
                int ny = current.y + dir;
                if(ny >=0 && ny < M && grid[current.x][ny] != '#'){
                    // After moving, need to fall
                    int fx = current.x, fy = ny;
                    while(1){
                        int next_under = fx + dx[g];
                        if(next_under <0 || next_under >=N || grid[next_under][fy] == '#'){
                            break;
                        }
                        fx = next_under;
                    }
                    if(visited[fx][fy][g]==-1){
                        visited[fx][fy][g] = visited[current.x][current.y][g];
                        queue[tail++] = (State){fx, fy, g};
                    }
                }
            }
            // Flip gravity
            int ng = g ^ 1;
            int fx = current.x;
            while(1){
                int next_under = fx + dx[ng];
                if(next_under <0 || next_under >=N || grid[next_under][current.y] == '#'){
                    break;
                }
                fx = next_under;
            }
            if(fx >=0 && fx <N && visited[fx][current.y][ng]==-1){
                visited[fx][current.y][ng] = visited[current.x][current.y][g] + 1;
                queue[tail++] = (State){fx, current.y, ng};
            }
        }
        else{
            // Fall to under
            int fx = under;
            int fy = current.y;
            if(fx >=0 && fx <N && grid[fx][fy] != '#'){
                if(visited[fx][fy][g]==-1){
                    visited[fx][fy][g] = visited[current.x][current.y][g];
                    queue[tail++] = (State){fx, fy, g};
                }
            }
        }
    }
    printf("-1");
}
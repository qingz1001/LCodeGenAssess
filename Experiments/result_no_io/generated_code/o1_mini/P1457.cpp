#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

int m, n;
int grid[MAX][MAX];
int visited[MAX][MAX];
int room_id = 1;
int room_size[MAX*MAX];
int dr[4] = { -1, 0, 1, 0 }; // N, E, S, W
int dc[4] = { 0, 1, 0, -1 };

typedef struct {
    int r;
    int c;
} Queue;

int main(){
    scanf("%d %d", &m, &n);
    for(int r=0;r<n;r++) {
        for(int c=0;c<m;c++) {
            scanf("%d", &grid[r][c]);
        }
    }

    // BFS
    Queue q[MAX*MAX];
    int front, rear;
    for(int r=0;r<n;r++) {
        for(int c=0;c<m;c++) {
            if(!visited[r][c]){
                front = 0;
                rear = 0;
                q[rear].r = r;
                q[rear].c = c;
                rear++;
                visited[r][c] = room_id;
                room_size[room_id] = 1;
                while(front < rear){
                    int curr_r = q[front].r;
                    int curr_c = q[front].c;
                    front++;
                    int walls = grid[curr_r][curr_c];
                    for(int d=0; d<4; d++){
                        if(!(walls & (1 << d))){
                            int nr = curr_r + dr[d];
                            int nc = curr_c + dc[d];
                            if(nr >=0 && nr <n && nc >=0 && nc <m && !visited[nr][nc]){
                                visited[nr][nc] = room_id;
                                room_size[room_id]++;
                                q[rear].r = nr;
                                q[rear].c = nc;
                                rear++;
                            }
                        }
                    }
                }
                room_id++;
            }
        }
    }
    int total_rooms = room_id -1;
    int max_room = 0;
    for(int i=1;i<=total_rooms;i++) {
        if(room_size[i] > max_room){
            max_room = room_size[i];
        }
    }

    // Find the best wall to remove
    int combined_max = 0;
    int best_r = 0, best_c =0;
    char best_dir = 'N';

    for(int c=0;c<m;c++) {
        for(int r=n-1;r>=0;r--){
            // Try North
            if(r >0){
                if(grid[r][c] & 2){
                    int room1 = visited[r][c];
                    int room2 = visited[r-1][c];
                    if(room1 != room2){
                        int combined = room_size[room1] + room_size[room2];
                        if(combined > combined_max){
                            combined_max = combined;
                            best_r = r;
                            best_c = c;
                            best_dir = 'N';
                        }
                    }
                }
            }
            // Try East
            if(c < m-1){
                if(grid[r][c] & 4){
                    int room1 = visited[r][c];
                    int room2 = visited[r][c+1];
                    if(room1 != room2){
                        int combined = room_size[room1] + room_size[room2];
                        if(combined > combined_max){
                            combined_max = combined;
                            best_r = r;
                            best_c = c;
                            best_dir = 'E';
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", total_rooms);
    printf("%d\n", max_room);
    printf("%d\n", combined_max);
    printf("%d %d %c\n", best_r+1, best_c+1, best_dir);
    return 0;
}
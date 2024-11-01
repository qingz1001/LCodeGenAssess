#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int m, n;
int grid[MAX][MAX];
int visited[MAX][MAX];
int room_size[MAX * MAX];
int room_id = 1;
int dr[4] = {0, -1, 0, 1}; // West, North, East, South
int dc[4] = {-1, 0, 1, 0};

void dfs(int r, int c, int id, int *size) {
    visited[r][c] = id;
    (*size)++;
    for(int i=0;i<4;i++) {
        if(!(grid[r][c] & (1 << i))) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr >=0 && nr < n && nc >=0 && nc < m && !visited[nr][nc]){
                dfs(nr, nc, id, size);
            }
        }
    }
}

int main(){
    scanf("%d %d", &m, &n);
    for(int r=0;r<n;r++) {
        for(int c=0;c<m;c++) {
            scanf("%d", &grid[r][c]);
        }
    }
    // Find rooms
    for(int r=0;r<n;r++) {
        for(int c=0;c<m;c++) {
            if(!visited[r][c]){
                room_size[room_id] = 0;
                dfs(r, c, room_id, &room_size[room_id]);
                room_id++;
            }
        }
    }
    int total_rooms = room_id -1;
    int max_room = 0;
    for(int i=1;i<=total_rooms;i++) if(room_size[i] > max_room) max_room = room_size[i];
    // Check walls to remove
    int max_comb = 0;
    int remove_r, remove_c;
    char remove_dir;
    for(int c=0;c<m;c++) {
        for(int r=n-1;r>=0;r--){
            if(grid[r][c] & 2){ // North wall
                if(r >0){
                    int room1 = visited[r][c];
                    int room2 = visited[r-1][c];
                    if(room1 != room2){
                        int combined = room_size[room1] + room_size[room2];
                        if(combined > max_comb){
                            max_comb = combined;
                            remove_r = r;
                            remove_c = c;
                            remove_dir = 'N';
                        }
                    }
                }
            }
            if(grid[r][c] & 4){ // East wall
                if(c < m-1){
                    int room1 = visited[r][c];
                    int room2 = visited[r][c+1];
                    if(room1 != room2){
                        int combined = room_size[room1] + room_size[room2];
                        if(combined > max_comb){
                            max_comb = combined;
                            remove_r = r;
                            remove_c = c;
                            remove_dir = 'E';
                        }
                    }
                }
            }
        }
    }
    if(max_comb ==0){
        max_comb = max_room;
    }
    printf("%d\n%d\n%d\n%d %d %c\n", total_rooms, max_room, max_comb, remove_r+1, remove_c+1, remove_dir);
    return 0;
}
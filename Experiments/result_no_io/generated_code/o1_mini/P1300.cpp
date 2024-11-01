#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30
#define INF 1000000

typedef struct {
    int x, y, dir;
    int cost;
} State;

int h, w;
char grid[MAX][MAX+1];
int cost_grid[MAX][MAX][4];
int visited_grid[MAX][MAX][4];

// Directions: 0 - North, 1 - East, 2 - South, 3 - West
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int min(int a, int b) { return a < b ? a : b; }

// Priority Queue using simple array (since V is small)
#define QUEUE_SIZE 100000
State queue_arr[QUEUE_SIZE];
int front = 0, rear = 0;

void enqueue(State s) {
    int i = rear++;
    while (i > front) {
        if (queue_arr[i-1].cost <= s.cost) break;
        queue_arr[i] = queue_arr[i-1];
        i--;
    }
    queue_arr[i] = s;
}

State dequeue() {
    return queue_arr[front++];
}

int main(){
    scanf("%d %d", &h, &w);
    int start_x, start_y, start_dir;
    int end_x, end_y;
    for(int i=0;i<h;i++){
        scanf("%s", grid[i]);
        for(int j=0;j<w;j++){
            if(grid[i][j] == 'E' || grid[i][j] == 'W' || grid[i][j] == 'N' || grid[i][j] == 'S'){
                start_x = i;
                start_y = j;
                switch(grid[i][j]){
                    case 'N': start_dir = 0; break;
                    case 'E': start_dir = 1; break;
                    case 'S': start_dir = 2; break;
                    case 'W': start_dir = 3; break;
                }
            }
            if(grid[i][j] == 'F'){
                end_x = i;
                end_y = j;
            }
        }
    }

    // Initialize cost array
    for(int i=0;i<h;i++) {
        for(int j=0;j<w;j++) {
            for(int d=0;d<4;d++) {
                cost_grid[i][j][d] = INF;
                visited_grid[i][j][d] = 0;
            }
        }
    }

    // Initialize starting state
    State start = {start_x, start_y, start_dir, 0};
    cost_grid[start_x][start_y][start_dir] = 0;
    enqueue(start);

    while(front < rear){
        State current = dequeue();
        if(visited_grid[current.x][current.y][current.dir]) continue;
        visited_grid[current.x][current.y][current.dir] = 1;

        if(current.x == end_x && current.y == end_y){
            printf("%d\n", current.cost);
            return 0;
        }

        // Move Forward
        int nx = current.x + dx[current.dir];
        int ny = current.y + dy[current.dir];
        if(nx >=0 && nx < h && ny >=0 && ny < w && grid[nx][ny] != '.'){
            if(cost_grid[nx][ny][current.dir] > current.cost){
                cost_grid[nx][ny][current.dir] = current.cost;
                State next = {nx, ny, current.dir, current.cost};
                enqueue(next);
            }
        }

        // Turn Left
        int left_dir = (current.dir + 3) % 4;
        int lx = current.x + dx[left_dir];
        int ly = current.y + dy[left_dir];
        if(lx >=0 && lx < h && ly >=0 && ly < w && grid[lx][ly] != '.'){
            int new_cost = current.cost + 1;
            if(cost_grid[lx][ly][left_dir] > new_cost){
                cost_grid[lx][ly][left_dir] = new_cost;
                State next = {lx, ly, left_dir, new_cost};
                enqueue(next);
            }
        }

        // Turn Right
        int right_dir = (current.dir + 1) % 4;
        int rx = current.x + dx[right_dir];
        int ry = current.y + dy[right_dir];
        if(rx >=0 && rx < h && ry >=0 && ry < w && grid[rx][ry] != '.'){
            int new_cost = current.cost + 5;
            if(cost_grid[rx][ry][right_dir] > new_cost){
                cost_grid[rx][ry][right_dir] = new_cost;
                State next = {rx, ry, right_dir, new_cost};
                enqueue(next);
            }
        }

        // Check if forward, left, right are blocked
        int forward_block = !(nx >=0 && nx < h && ny >=0 && ny < w && grid[nx][ny] != '.');
        int left_block = !(lx >=0 && lx < h && ly >=0 && ly < w && grid[lx][ly] != '.');
        int right_block = !(rx >=0 && rx < h && ry >=0 && ry < w && grid[rx][ry] != '.');
        if(forward_block && left_block && right_block){
            int u_dir = (current.dir + 2) % 4;
            int ux = current.x + dx[u_dir];
            int uy = current.y + dy[u_dir];
            if(ux >=0 && ux < h && uy >=0 && uy < w && grid[ux][uy] != '.'){
                int new_cost = current.cost + 10;
                if(cost_grid[ux][uy][u_dir] > new_cost){
                    cost_grid[ux][uy][u_dir] = new_cost;
                    State next = {ux, uy, u_dir, new_cost};
                    enqueue(next);
                }
            }
        }
    }

    return 0;
}
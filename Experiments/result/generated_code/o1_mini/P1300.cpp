#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_H 30
#define MAX_W 30
#define MAX_DIR 4
#define INF 1000000000

typedef struct {
    int cost;
    int x, y, dir;
} Node;

typedef struct {
    Node heap[90000];
    int size;
} PriorityQueue;

void push_heap(PriorityQueue *pq, Node node) {
    int i = pq->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->heap[parent].cost <= node.cost)
            break;
        pq->heap[i] = pq->heap[parent];
        i = parent;
    }
    pq->heap[i] = node;
}

Node pop_heap_func(PriorityQueue *pq) {
    Node top = pq->heap[0];
    Node last = pq->heap[--pq->size];
    int i = 0, child;
    while ((child = 2 * i + 1) < pq->size) {
        if (child + 1 < pq->size && pq->heap[child + 1].cost < pq->heap[child].cost)
            child++;
        if (last.cost <= pq->heap[child].cost)
            break;
        pq->heap[i] = pq->heap[child];
        i = child;
    }
    pq->heap[i] = last;
    return top;
}

int main(){
    int h, w;
    scanf("%d %d", &h, &w);
    char grid[MAX_H][MAX_W+1];
    for(int i=0;i<h;i++){
        scanf("%s", grid[i]);
    }
    int start_x, start_y, start_dir;
    int end_x, end_y;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(grid[i][j]=='E' || grid[i][j]=='W' || grid[i][j]=='N' || grid[i][j]=='S'){
                start_x = i;
                start_y = j;
                if(grid[i][j]=='N') start_dir=0;
                else if(grid[i][j]=='E') start_dir=1;
                else if(grid[i][j]=='S') start_dir=2;
                else start_dir=3;
            }
            if(grid[i][j]=='F'){
                end_x = i;
                end_y = j;
            }
        }
    }
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};
    int dist[MAX_H][MAX_W][4];
    for(int i=0;i<h;i++) {
        for(int j=0;j<w;j++) {
            for(int d=0;d<4;d++) {
                dist[i][j][d] = INF;
            }
        }
    }
    PriorityQueue pq;
    pq.size = 0;
    Node start = {0, start_x, start_y, start_dir};
    push_heap(&pq, start);
    dist[start_x][start_y][start_dir] = 0;
    while(pq.size >0){
        Node current = pop_heap_func(&pq);
        if(current.x == end_x && current.y == end_y){
            printf("%d", current.cost);
            return 0;
        }
        if(current.cost > dist[current.x][current.y][current.dir])
            continue;
        // Determine possible moves
        int dirs_to_try[3];
        int costs[3];
        int count =0;
        // Forward
        int f_dir = current.dir;
        int f_x = current.x + dx[f_dir];
        int f_y = current.y + dy[f_dir];
        if(f_x >=0 && f_x <h && f_y >=0 && f_y <w && (grid[f_x][f_y]=='#' || grid[f_x][f_y]=='F')){
            dirs_to_try[count] = f_dir;
            costs[count] = 0;
            count++;
        }
        // Left
        int l_dir = (current.dir +3)%4;
        int l_x = current.x + dx[l_dir];
        int l_y = current.y + dy[l_dir];
        if(l_x >=0 && l_x <h && l_y >=0 && l_y <w && (grid[l_x][l_y]=='#' || grid[l_x][l_y]=='F')){
            dirs_to_try[count] = l_dir;
            costs[count] = 1;
            count++;
        }
        // Right
        int r_dir = (current.dir +1)%4;
        int r_x = current.x + dx[r_dir];
        int r_y = current.y + dy[r_dir];
        if(r_x >=0 && r_x <h && r_y >=0 && r_y <w && (grid[r_x][r_y]=='#' || grid[r_x][r_y]=='F')){
            dirs_to_try[count] = r_dir;
            costs[count] = 5;
            count++;
        }
        if(count >0){
            for(int i=0;i<count;i++){
                int ndir = dirs_to_try[i];
                int nx = (i==0)? f_x : ((i==1)? l_x : r_x);
                int ny = (i==0)? f_y : ((i==1)? l_y : r_y);
                int new_cost = current.cost + costs[i];
                if(new_cost < dist[nx][ny][ndir]){
                    dist[nx][ny][ndir] = new_cost;
                    Node next = {new_cost, nx, ny, ndir};
                    push_heap(&pq, next);
                }
            }
        }
        else{
            // Try U-turn
            int u_dir = (current.dir +2)%4;
            int u_x = current.x + dx[u_dir];
            int u_y = current.y + dy[u_dir];
            if(u_x >=0 && u_x <h && u_y >=0 && u_y <w && (grid[u_x][u_y]=='#' || grid[u_x][u_y]=='F')){
                int new_cost = current.cost +10;
                if(new_cost < dist[u_x][u_y][u_dir]){
                    dist[u_x][u_y][u_dir] = new_cost;
                    Node next = {new_cost, u_x, u_y, u_dir};
                    push_heap(&pq, next);
                }
            }
        }
    }
    return 0;
}
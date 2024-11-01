#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_Y 7
#define MAX_X 5
#define MAX_COL_HEIGHT 7
#define MAX_MOVES 5
#define MAX_PATH (MAX_MOVES * 3)

typedef struct {
    int grid[MAX_Y][MAX_X];
    int steps;
    int path[MAX_MOVES][3];
} State;

typedef struct {
    State* data;
    int front, rear, size, capacity;
} Queue;

Queue* createQueue(int capacity){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (State*)malloc(sizeof(State)*capacity);
    q->front = q->rear = q->size = 0;
    q->capacity = capacity;
    return q;
}

int isEmpty(Queue* q){
    return q->size ==0;
}

void enqueue(Queue* q, State s){
    if(q->size == q->capacity){
        q->capacity *=2;
        q->data = (State*)realloc(q->data, sizeof(State)*q->capacity);
    }
    q->data[q->rear++] = s;
    q->rear %= q->capacity;
    q->size++;
}

State dequeue(Queue* q){
    State s = q->data[q->front++];
    q->front %= q->capacity;
    q->size--;
    return s;
}

int deepCopyGrid(int src[MAX_Y][MAX_X], int dest[MAX_Y][MAX_X]){
    memcpy(dest, src, sizeof(int)*MAX_Y*MAX_X);
    return 0;
}

int eliminate(int grid[MAX_Y][MAX_X]){
    int marked[MAX_Y][MAX_X];
    memset(marked, 0, sizeof(marked));
    // Check rows
    for(int y=0;y<MAX_Y;y++){
        int cnt=1;
        for(int x=1;x<MAX_X;x++){
            if(grid[y][x] !=0 && grid[y][x] == grid[y][x-1]){
                cnt++;
            }
            else{
                if(cnt >=3){
                    for(int k=x-1; k>=x-cnt; k--) marked[y][k]=1;
                }
                cnt=1;
            }
        }
        if(cnt >=3){
            for(int k=MAX_X-1; k>=MAX_X - cnt; k--) marked[y][k]=1;
        }
    }
    // Check columns
    for(int x=0;x<MAX_X;x++){
        int cnt=1;
        for(int y=1;y<MAX_Y;y++){
            if(grid[y][x]!=0 && grid[y][x]==grid[y-1][x]){
                cnt++;
            }
            else{
                if(cnt >=3){
                    for(int k=y-1; k>=y-cnt; k--) marked[k][x]=1;
                }
                cnt=1;
            }
        }
        if(cnt >=3){
            for(int k=MAX_Y-1; k>=MAX_Y - cnt; k--) marked[k][x]=1;
        }
    }
    // Check if any marked
    int any =0;
    for(int y=0;y<MAX_Y;y++) for(int x=0;x<MAX_X;x++) if(marked[y][x]) {any=1;}
    if(!any) return 0;
    // Remove marked
    for(int x=0;x<MAX_X;x++){
        int idx=0;
        for(int y=0;y<MAX_Y;y++) if(!marked[y][x]) grid[idx++][x] = grid[y][x];
        for(; idx<MAX_Y; idx++) grid[idx][x]=0;
    }
    return 1;
}

int applyElimination(int grid[MAX_Y][MAX_X]){
    while(eliminate(grid));
    return 0;
}

int moveBlock(int grid[MAX_Y][MAX_X], int x, int y, int g, int newGrid[MAX_Y][MAX_X]){
    deepCopyGrid(grid, newGrid);
    if(newGrid[y][x] ==0) return -1;
    if(g ==1){
        if(x == MAX_X-1) return -1;
        if(newGrid[y][x+1] !=0){
            // Swap
            int tmp = newGrid[y][x];
            newGrid[y][x] = newGrid[y][x+1];
            newGrid[y][x+1] = tmp;
        }
        else{
            // Move to x+1 and let it fall
            int color = newGrid[y][x];
            newGrid[y][x] =0;
            int ny =0;
            while(ny < MAX_Y && newGrid[ny][x+1]==0) ny++;
            ny--;
            if(ny <0) return -1;
            newGrid[ny][x+1] = color;
        }
    }
    else if(g ==-1){
        if(x ==0) return -1;
        if(newGrid[y][x-1] !=0){
            // Swap
            int tmp = newGrid[y][x];
            newGrid[y][x] = newGrid[y][x-1];
            newGrid[y][x-1] = tmp;
        }
        else{
            // Move to x-1 and let it fall
            int color = newGrid[y][x];
            newGrid[y][x] =0;
            int ny =0;
            while(ny < MAX_Y && newGrid[ny][x-1]==0) ny++;
            ny--;
            if(ny <0) return -1;
            newGrid[ny][x-1] = color;
        }
    }
    applyElimination(newGrid);
    return 0;
}

int isEmpty(int grid[MAX_Y][MAX_X]){
    for(int y=0;y<MAX_Y;y++) for(int x=0;x<MAX_X;x++) if(grid[y][x]!=0) return 0;
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);
    State initial;
    memset(initial.grid, 0, sizeof(initial.grid));
    for(int x=0;x<MAX_X;x++){
        int val;
        int y=0;
        while(scanf("%d", &val) && val !=0){
            if(y < MAX_Y) initial.grid[y][x] = val;
            y++;
        }
    }
    initial.steps =0;
    memset(initial.path, 0, sizeof(initial.path));
    Queue* q = createQueue(1000000);
    enqueue(q, initial);
    int found =0;
    State answer;
    while(!isEmpty(q)){
        State current = dequeue(q);
        if(current.steps > n) continue;
        if(isEmpty(current.grid)){
            if(current.steps <=n){
                for(int i=0;i<current.steps;i++) printf("%d %d %d\n", current.path[i][0], current.path[i][1], current.path[i][2]);
                return 0;
            }
            continue;
        }
        if(current.steps ==n) continue;
        for(int x=0;x<MAX_X;x++) {
            for(int y=0;y<MAX_Y;y++) {
                if(current.grid[y][x]==0) continue;
                for(int g =1; g>=-1; g-=2){
                    State next;
                    deepCopyGrid(current.grid, next.grid);
                    memcpy(next.path, current.path, sizeof(current.path));
                    if(moveBlock(current.grid, x, y, g, next.grid)==-1) continue;
                    next.steps = current.steps +1;
                    next.path[next.steps-1][0] =x;
                    next.path[next.steps-1][1] =y;
                    next.path[next.steps-1][2] =g;
                    enqueue(q, next);
                }
            }
        }
    }
    printf("-1\n");
    return 0;
}
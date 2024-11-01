#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STEPS 5
#define ROWS 7
#define COLS 5
#define MAX_COL_HEIGHT 7
#define MAX_COLOR 10

typedef struct {
    int grid[ROWS][COLS];
} State;

typedef struct Node {
    State state;
    int step;
    int moves[MAX_STEPS][3];
} Node;

typedef struct QueueNode {
    Node node;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void enqueue(Queue* q, Node node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;
    if(q->rear) q->rear->next = newNode;
    else q->front = newNode;
    q->rear = newNode;
}

int dequeue(Queue* q, Node* node) {
    if(q->front == NULL) return 0;
    QueueNode* temp = q->front;
    *node = temp->node;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    free(temp);
    return 1;
}

int is_empty(Queue* q) {
    return q->front == NULL;
}

unsigned long hash_state(int grid[ROWS][COLS]) {
    unsigned long hash = 0;
    for(int y=0;y<ROWS;y++) {
        for(int x=0;x<COLS;x++) {
            hash = hash * 11 + grid[y][x];
        }
    }
    return hash;
}

int visited_hash[10000000] = {0};

int find_and_remove(State* state) {
    int mark[ROWS][COLS];
    memset(mark, 0, sizeof(mark));
    // Check rows
    for(int y=0;y<ROWS;y++) {
        int cnt=1;
        for(int x=1;x<COLS;x++) {
            if(state->grid[y][x] !=0 && state->grid[y][x] == state->grid[y][x-1]) {
                cnt++;
            }
            else {
                if(cnt >=3){
                    for(int k=x-1; k>=x-cnt; k--) mark[y][k]=1;
                }
                cnt=1;
            }
        }
        if(cnt >=3){
            for(int k=COLS-1; k>=COLS - cnt; k--) mark[y][k]=1;
        }
    }
    // Check columns
    for(int x=0;x<COLS;x++) {
        int cnt=1;
        for(int y=1;y<ROWS;y++) {
            if(state->grid[y][x] !=0 && state->grid[y][x] == state->grid[y-1][x]) {
                cnt++;
            }
            else {
                if(cnt >=3){
                    for(int k=y-1; k>=y-cnt; k--) mark[k][x]=1;
                }
                cnt=1;
            }
        }
        if(cnt >=3){
            for(int k=ROWS-1; k>=ROWS - cnt; k--) mark[k][x]=1;
        }
    }
    // Remove marked and apply gravity
    int removed=0;
    for(int x=0;x<COLS;x++) {
        int pointer=0;
        for(int y=0;y<ROWS;y++) {
            if(!mark[y][x]) {
                state->grid[pointer][x] = state->grid[y][x];
                pointer++;
            }
            else {
                state->grid[y][x] =0;
                removed=1;
            }
        }
        for(int y=pointer;y<ROWS;y++) state->grid[y][x]=0;
    }
    return removed;
}

int apply_elimination(State* state) {
    while(1){
        if(!find_and_remove(state)) break;
    }
    return 1;
}

int is_empty_grid(State* state){
    for(int y=0;y<ROWS;y++) {
        for(int x=0;x<COLS;x++) {
            if(state->grid[y][x]!=0) return 0;
        }
    }
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);
    State initial;
    memset(initial.grid, 0, sizeof(initial.grid));
    for(int x=0; x<COLS; x++) {
        int num;
        int y=0;
        while(scanf("%d", &num) && num !=0){
            if(y < ROWS){
                initial.grid[y][x] = num;
                y++;
            }
        }
    }
    Queue q;
    q.front = q.rear = NULL;
    Node start;
    start.state = initial;
    start.step =0;
    memset(start.moves, 0, sizeof(start.moves));
    enqueue(&q, start);
    unsigned long h = hash_state(initial.grid);
    visited_hash[h] =1;
    while(!is_empty(&q)){
        Node current;
        dequeue(&q, &current);
        if(current.step == n){
            if(is_empty_grid(&current.state)){
                for(int i=0;i<n;i++) printf("%d %d %d\n", current.moves[i][0], current.moves[i][1], current.moves[i][2]);
                return 0;
            }
            continue;
        }
        for(int x=0;x<COLS;x++) {
            for(int y=0;y<ROWS;y++) {
                if(current.state.grid[y][x]==0) continue;
                for(int dir=1; dir>=-1; dir-=2){
                    if(dir ==1 && x == COLS-1) continue;
                    if(dir ==-1 && x ==0) continue;
                    State new_state = current.state;
                    if(dir ==1){
                        if(new_state.grid[y][x+1]!=0){
                            // Swap
                            int temp = new_state.grid[y][x];
                            new_state.grid[y][x] = new_state.grid[y][x+1];
                            new_state.grid[y][x+1] = temp;
                        }
                        else{
                            // Move right and drop
                            new_state.grid[y][x] =0;
                            int ny = y;
                            while(ny < ROWS-1 && new_state.grid[ny+1][x+1]==0) ny++;
                            if(x+1 < COLS && ny < ROWS){
                                new_state.grid[ny][x+1] = current.state.grid[y][x];
                            }
                        }
                    }
                    else{
                        if(new_state.grid[y][x-1]!=0){
                            // Swap
                            int temp = new_state.grid[y][x];
                            new_state.grid[y][x] = new_state.grid[y][x-1];
                            new_state.grid[y][x-1] = temp;
                        }
                        else{
                            // Move left and drop
                            new_state.grid[y][x] =0;
                            int ny = y;
                            while(ny < ROWS-1 && new_state.grid[ny+1][x-1]==0) ny++;
                            if(x-1 >=0 && ny < ROWS){
                                new_state.grid[ny][x-1] = current.state.grid[y][x];
                            }
                        }
                    }
                    apply_elimination(&new_state);
                    unsigned long nh = hash_state(new_state.grid);
                    if(!visited_hash[nh]){
                        visited_hash[nh]=1;
                        Node next = current;
                        next.state = new_state;
                        next.step +=1;
                        next.moves[next.step-1][0] =x;
                        next.moves[next.step-1][1] =y;
                        next.moves[next.step-1][2] =dir;
                        enqueue(&q, next);
                    }
                }
            }
        }
    }
    printf("-1\n");
    return 0;
}
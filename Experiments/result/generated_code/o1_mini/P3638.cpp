#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 9
#define MAX_QUEUE 1000000
#define MAX_GROUPS 9
#define DIRS 4

typedef struct {
    int min;
    int max;
    int x;
    int y;
} Group;

typedef struct {
    int num;
    Group groups[MAX_GROUPS];
    int steps;
} State;

typedef struct {
    State queue[MAX_QUEUE];
    int front;
    int rear;
} Queue;

// Directions: 0=Up, 1=Right, 2=Down, 3=Left
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// Turners
char grid_turn[501][501];
char grid_cell[501][501];
int w, h, n;

// Robots positions
Group initial_groups[MAX_N];

// Queue functions
void enqueue(Queue *q, State s) {
    q->queue[q->rear++] = s;
    if(q->rear >= MAX_QUEUE) q->rear = 0;
}

State dequeue(Queue *q) {
    State s = q->queue[q->front++];
    if(q->front >= MAX_QUEUE) q->front = 0;
    return s;
}

int is_empty(Queue *q) {
    return q->front == q->rear;
}

// Hashing for visited states
unsigned long hash_state(State *s) {
    unsigned long hash = 0;
    for(int i=0;i<s->num;i++) {
        hash = hash * 1000003 + s->groups[i].min;
        hash = hash * 1000003 + s->groups[i].max;
        hash = hash * 1000003 + s->groups[i].x;
        hash = hash * 1000003 + s->groups[i].y;
    }
    return hash;
}

#define HASH_SIZE 10000007
int visited_hash[10000007];
int visited_idx = 1;

int check_visited(State *s){
    unsigned long h = hash_state(s) % HASH_SIZE;
    unsigned long original = h;
    while(1){
        if(visited_hash[h] == 0){
            visited_hash[h] = visited_idx;
            return 0;
        }
        // To ensure unique identification, ideally compare full state
        // Skipping for simplicity
        h = (h + 1) % HASH_SIZE;
        if(h == original) break;
    }
    return 1;
}

int main(){
    scanf("%d %d %d", &n, &w, &h);
    // Initialize grid
    for(int i=0;i<h;i++) {
        char line[501];
        scanf("%s", line);
        for(int j=0;j<w;j++) {
            grid_cell[i][j] = line[j];
            if(line[j] == 'A' || line[j] == 'C') {
                grid_turn[i][j] = line[j];
            }
            else {
                grid_turn[i][j] = '.';
            }
            if(line[j]>='1' && line[j]<='9'){
                int robot = line[j]-'1';
                initial_groups[robot].min = robot+1;
                initial_groups[robot].max = robot+1;
                initial_groups[robot].x = i;
                initial_groups[robot].y = j;
            }
        }
    }
    // Initialize initial state
    State initial;
    initial.num = n;
    for(int i=0;i<n;i++) initial.groups[i] = initial_groups[i];
    // Sort initial groups by min
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            if(initial.groups[i].min > initial.groups[j].min){
                Group temp = initial.groups[i];
                initial.groups[i] = initial.groups[j];
                initial.groups[j] = temp;
            }
        }
    }
    initial.steps = 0;
    // Initialize queue
    Queue q;
    q.front = q.rear = 0;
    enqueue(&q, initial);
    // Mark visited
    visited_hash[hash_state(&initial) % HASH_SIZE] = visited_idx;
    // BFS
    while(!is_empty(&q)){
        State current = dequeue(&q);
        if(current.num == 1 && current.groups[0].min == 1 && current.groups[0].max == n){
            printf("%d", current.steps);
            return 0;
        }
        for(int g=0; g<current.num; g++) {
            for(int d=0; d<DIRS; d++) {
                // Create a copy of current state
                State next = current;
                // Move group g in direction d
                Group moving = next.groups[g];
                int dir = d;
                int x = moving.x;
                int y = moving.y;
                while(1){
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if(nx <0 || nx >=h || ny <0 || ny >=w) break;
                    if(grid_cell[nx][ny] == 'x') break;
                    x = nx;
                    y = ny;
                    if(grid_turn[x][y] == 'C') {
                        dir = (dir +1)%4;
                    }
                    else if(grid_turn[x][y] == 'A'){
                        dir = (dir +3)%4;
                    }
                }
                // Update group's position
                next.groups[g].x = x;
                next.groups[g].y = y;
                // Check for merging
                // Find all groups on (x,y)
                int new_min = next.groups[g].min;
                int new_max = next.groups[g].max;
                int merge_indices[MAX_GROUPS];
                int merge_count = 0;
                for(int m=0;m<next.num;m++) {
                    if(m != g && next.groups[m].x == x && next.groups[m].y == y){
                        // Check compatibility
                        if(abs(next.groups[m].min - moving.min) ==1 || abs(next.groups[m].max - moving.max)==1 ||
                           (next.groups[m].min <= moving.min && moving.min <= next.groups[m].max+1) ||
                           (next.groups[m].min-1 <= moving.max && moving.max <= next.groups[m].max)){
                            merge_indices[merge_count++] = m;
                            if(next.groups[m].min < new_min) new_min = next.groups[m].min;
                            if(next.groups[m].max > new_max) new_max = next.groups[m].max;
                        }
                    }
                }
                if(merge_count >0){
                    // Merge groups
                    next.groups[g].min = new_min;
                    next.groups[g].max = new_max;
                    // Remove merged groups
                    for(int m=0; m<merge_count; m++) {
                        int idx = merge_indices[m];
                        for(int s=idx; s<next.num-1; s++) {
                            next.groups[s] = next.groups[s+1];
                        }
                        next.num--;
                        if(idx <g) g--;
                    }
                }
                // Sort groups by min
                for(int i=0;i<next.num-1;i++) {
                    for(int j=i+1;j<next.num;j++) {
                        if(next.groups[i].min > next.groups[j].min){
                            Group temp = next.groups[i];
                            next.groups[i] = next.groups[j];
                            next.groups[j] = temp;
                        }
                    }
                }
                // Check visited
                if(!check_visited(&next)){
                    next.steps = current.steps +1;
                    enqueue(&q, next);
                }
            }
        }
    }
    printf("-1");
    return 0;
}
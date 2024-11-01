#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GROUPS 9
#define MAX_QUEUE 1000000
#define MAX_STATE_KEY 1000

typedef struct {
    int mask; // bitmask representing robots in the group
    int x, y;
} Group;

typedef struct {
    Group groups[MAX_GROUPS];
    int group_count;
    int steps;
} State;

typedef struct {
    State states[MAX_QUEUE];
    int front, rear;
} Queue;

unsigned long long visited_hashes[10000007];
int hash_size = 10000007;

unsigned long long hash_state(State *s) {
    unsigned long long hash = 0;
    for(int i=0;i<s->group_count;i++) {
        hash = hash * 1000003 + s->groups[i].mask;
        hash = hash * 1000003 + s->groups[i].x;
        hash = hash * 1000003 + s->groups[i].y;
    }
    return hash;
}

int is_visited(State *s) {
    unsigned long long h = hash_state(s) % hash_size;
    unsigned long long key = hash_state(s);
    while(visited_hashes[h] != 0) {
        if(visited_hashes[h] == key) return 1;
        h = (h + 1) % hash_size;
    }
    return 0;
}

void mark_visited(State *s) {
    unsigned long long h = hash_state(s) % hash_size;
    unsigned long long key = hash_state(s);
    while(visited_hashes[h] != 0) {
        if(visited_hashes[h] == key) return;
        h = (h + 1) % hash_size;
    }
    visited_hashes[h] = key;
}

void enqueue(Queue *q, State *s) {
    if(q->rear >= MAX_QUEUE) return;
    q->states[q->rear++] = *s;
}

int dequeue(Queue *q, State *s) {
    if(q->front >= q->rear) return 0;
    *s = q->states[q->front++];
    return 1;
}

int n, w, h;
char grid[500][501];
Group initial_groups[9];
int initial_group_count = 0;

int dx[4] = {0, 1, 0, -1}; // up, right, down, left
int dy[4] = { -1, 0, 1, 0 };
typedef enum {UP, RIGHT, DOWN, LEFT} DIR;

int main(){
    scanf("%d %d %d", &n, &w, &h);
    for(int i=0;i<h;i++) {
        scanf("%s", grid[i]);
        for(int j=0;j<w;j++) {
            if(grid[i][j]>='1' && grid[i][j]<='9') {
                initial_groups[initial_group_count].mask = 1 << (grid[i][j]-'1');
                initial_groups[initial_group_count].x = j;
                initial_groups[initial_group_count].y = i;
                initial_group_count++;
            }
        }
    }
    Queue q;
    q.front = q.rear = 0;
    State start;
    start.group_count = initial_group_count;
    for(int i=0;i<initial_group_count;i++) {
        start.groups[i] = initial_groups[i];
    }
    start.steps = 0;
    enqueue(&q, &start);
    mark_visited(&start);
    int target_mask = (1 << n) -1;
    while(dequeue(&q, &start)){
        // Check if any group has all robots
        for(int i=0;i<start.group_count;i++) {
            if(start.groups[i].mask == target_mask){
                printf("%d", start.steps);
                return 0;
            }
        }
        // Try pushing each group in 4 directions
        for(int gi=0; gi<start.group_count; gi++) {
            for(int d=0; d<4; d++) {
                // Create a copy of groups
                State new_state;
                new_state.steps = start.steps +1;
                new_state.group_count = start.group_count;
                for(int k=0;k<start.group_count;k++) {
                    new_state.groups[k] = start.groups[k];
                }
                // Move group gi in direction d
                DIR dir = d;
                int x = new_state.groups[gi].x;
                int y = new_state.groups[gi].y;
                DIR current_dir = dir;
                while(1){
                    int nx = x + dx[current_dir];
                    int ny = y + dy[current_dir];
                    if(nx <0 || nx >=w || ny <0 || ny >=h) break;
                    if(grid[ny][nx] == 'x') break;
                    x = nx;
                    y = ny;
                    if(grid[y][x] == 'A'){
                        current_dir = (current_dir +3)%4;
                    }
                    else if(grid[y][x] == 'C'){
                        current_dir = (current_dir +1)%4;
                    }
                }
                new_state.groups[gi].x = x;
                new_state.groups[gi].y = y;
                // Check for merging
                for(int k=0; k<new_state.group_count; k++) {
                    if(k != gi && new_state.groups[k].x == x && new_state.groups[k].y == y){
                        // Check if masks are consecutive
                        int mask1 = new_state.groups[gi].mask;
                        int mask2 = new_state.groups[k].mask;
                        int min1=10, max1=0, min2=10, max2=0;
                        for(int b=0;b<n;b++) {
                            if(mask1 & (1<<b)){
                                if(b+1 < min1) min1 = b+1;
                                if(b+1 > max1) max1 = b+1;
                            }
                            if(mask2 & (1<<b)){
                                if(b+1 < min2) min2 = b+1;
                                if(b+1 > max2) max2 = b+1;
                            }
                        }
                        if(abs(min1 - max2) ==1 || abs(min2 - max1)==1){
                            // Merge
                            new_state.groups[gi].mask |= new_state.groups[k].mask;
                            // Remove group k
                            for(int m=k; m<new_state.group_count-1; m++) {
                                new_state.groups[m] = new_state.groups[m+1];
                            }
                            new_state.group_count--;
                            k--;
                        }
                    }
                }
                // Sort groups to have a unique state
                for(int m=0; m<new_state.group_count-1; m++) {
                    for(int l=m+1; l<new_state.group_count; l++) {
                        if(new_state.groups[m].mask > new_state.groups[l].mask){
                            Group temp = new_state.groups[m];
                            new_state.groups[m] = new_state.groups[l];
                            new_state.groups[l] = temp;
                        }
                    }
                }
                // Check if visited
                if(!is_visited(&new_state)){
                    enqueue(&q, &new_state);
                    mark_visited(&new_state);
                }
            }
        }
    }
    printf("-1");
    return 0;
}
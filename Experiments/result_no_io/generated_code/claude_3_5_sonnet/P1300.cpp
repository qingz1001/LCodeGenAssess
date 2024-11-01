#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 30
#define MAX_W 30
#define INF 1000000000

int h, w;
char map[MAX_H][MAX_W];
int dist[MAX_H][MAX_W][4];
int dx[] = {0, 1, 0, -1};  // E, S, W, N
int dy[] = {1, 0, -1, 0};

typedef struct {
    int x, y, dir, cost;
} State;

typedef struct {
    State* data;
    int front, rear, size;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (State*)malloc(capacity * sizeof(State));
    q->front = q->rear = 0;
    q->size = capacity;
    return q;
}

void enqueue(Queue* q, State s) {
    q->data[q->rear] = s;
    q->rear = (q->rear + 1) % q->size;
}

State dequeue(Queue* q) {
    State s = q->data[q->front];
    q->front = (q->front + 1) % q->size;
    return s;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

int bfs(int sx, int sy, int sdir) {
    memset(dist, 0x3f, sizeof(dist));
    Queue* q = createQueue(MAX_H * MAX_W * 4);
    
    dist[sx][sy][sdir] = 0;
    enqueue(q, (State){sx, sy, sdir, 0});
    
    while (!isEmpty(q)) {
        State cur = dequeue(q);
        int x = cur.x, y = cur.y, dir = cur.dir, cost = cur.cost;
        
        if (map[x][y] == 'F') return cost;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            int ncost = cost;
            
            if (nx < 0 || nx >= h || ny < 0 || ny >= w || map[nx][ny] == '.') continue;
            
            if (i == dir) ncost += 0;
            else if ((i + 1) % 4 == dir || (dir + 1) % 4 == i) ncost += 5;
            else if ((i + 2) % 4 == dir) ncost += 10;
            else ncost += 1;
            
            if (ncost < dist[nx][ny][i]) {
                dist[nx][ny][i] = ncost;
                enqueue(q, (State){nx, ny, i, ncost});
            }
        }
    }
    
    free(q->data);
    free(q);
    return -1;
}

int main() {
    scanf("%d %d", &h, &w);
    int sx, sy, sdir;
    
    for (int i = 0; i < h; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < w; j++) {
            if (map[i][j] == 'E') { sx = i; sy = j; sdir = 0; }
            if (map[i][j] == 'S') { sx = i; sy = j; sdir = 1; }
            if (map[i][j] == 'W') { sx = i; sy = j; sdir = 2; }
            if (map[i][j] == 'N') { sx = i; sy = j; sdir = 3; }
        }
    }
    
    printf("%d\n", bfs(sx, sy, sdir));
    return 0;
}
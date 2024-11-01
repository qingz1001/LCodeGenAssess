#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 500
#define MAX_M 500
#define INF 0x3f3f3f3f

char grid[MAX_N][MAX_M];
int dist[MAX_N][MAX_M][2];
int n, m;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

typedef struct {
    int x, y, g, d;
} State;

typedef struct {
    State* arr;
    int front, rear, size;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (State*)malloc(capacity * sizeof(State));
    q->front = q->rear = 0;
    q->size = capacity;
    return q;
}

void enqueue(Queue* q, State s) {
    q->arr[q->rear] = s;
    q->rear = (q->rear + 1) % q->size;
}

State dequeue(Queue* q) {
    State s = q->arr[q->front];
    q->front = (q->front + 1) % q->size;
    return s;
}

bool isEmpty(Queue* q) {
    return q->front == q->rear;
}

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != '#';
}

int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    Queue* q = createQueue(MAX_N * MAX_M * 2);
    
    dist[sx][sy][0] = 0;
    enqueue(q, (State){sx, sy, 0, 0});
    
    while (!isEmpty(q)) {
        State cur = dequeue(q);
        int x = cur.x, y = cur.y, g = cur.g, d = cur.d;
        
        if (x == ex && y == ey) return d;
        
        if (g == 0) {
            if (x + 1 < n && grid[x+1][y] == '.') {
                x++;
            } else {
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (isValid(nx, ny) && dist[nx][ny][g] > d) {
                        dist[nx][ny][g] = d;
                        enqueue(q, (State){nx, ny, g, d});
                    }
                }
                if (dist[x][y][1] > d + 1) {
                    dist[x][y][1] = d + 1;
                    enqueue(q, (State){x, y, 1, d + 1});
                }
            }
        } else {
            if (x - 1 >= 0 && grid[x-1][y] == '.') {
                x--;
            } else {
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (isValid(nx, ny) && dist[nx][ny][g] > d) {
                        dist[nx][ny][g] = d;
                        enqueue(q, (State){nx, ny, g, d});
                    }
                }
                if (dist[x][y][0] > d + 1) {
                    dist[x][y][0] = d + 1;
                    enqueue(q, (State){x, y, 0, d + 1});
                }
            }
        }
    }
    
    free(q->arr);
    free(q);
    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    int sx, sy, ex, ey;
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'C') {
                sx = i; sy = j;
            } else if (grid[i][j] == 'D') {
                ex = i; ey = j;
            }
        }
    }
    
    int result = bfs(sx, sy, ex, ey);
    printf("%d\n", result);
    
    return 0;
}
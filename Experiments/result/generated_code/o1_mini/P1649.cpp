#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define INF 1000000

typedef struct {
    int x, y, dir, cost;
} Node;

typedef struct {
    Node *data;
    int size;
    int capacity;
} PriorityQueue;

// Directions: 0=up, 1=down, 2=left, 3=right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

PriorityQueue* createQueue(int capacity){
    PriorityQueue *q = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    q->data = (Node*)malloc(sizeof(Node)*capacity);
    q->size = 0;
    q->capacity = capacity;
    return q;
}

void swap(Node *a, Node *b){
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void pushQueue(PriorityQueue *q, Node node){
    if(q->size >= q->capacity){
        q->capacity *=2;
        q->data = (Node*)realloc(q->data, sizeof(Node)*q->capacity);
    }
    q->data[q->size] = node;
    int i = q->size;
    q->size++;
    // Heapify up
    while(i > 0){
        int parent = (i-1)/2;
        if(q->data[parent].cost > q->data[i].cost){
            swap(&q->data[parent], &q->data[i]);
            i = parent;
        }
        else break;
    }
}

Node popQueue(PriorityQueue *q){
    Node top = q->data[0];
    q->size--;
    q->data[0] = q->data[q->size];
    // Heapify down
    int i = 0;
    while(1){
        int left = 2*i +1;
        int right = 2*i +2;
        int smallest = i;
        if(left < q->size && q->data[left].cost < q->data[smallest].cost){
            smallest = left;
        }
        if(right < q->size && q->data[right].cost < q->data[smallest].cost){
            smallest = right;
        }
        if(smallest != i){
            swap(&q->data[i], &q->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    int N;
    scanf("%d", &N);
    char grid[MAXN][MAXN];
    int ax, ay, bx, by;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            char c;
            scanf(" %c", &c);
            grid[i][j] = c;
            if(c == 'A'){
                ax = i;
                ay = j;
            }
            if(c == 'B'){
                bx = i;
                by = j;
            }
        }
    }
    int min_turns[MAXN][MAXN][4];
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            for(int d=0;d<4;d++) {
                min_turns[i][j][d] = INF;
            }
        }
    }
    PriorityQueue *pq = createQueue(100000);
    // Initialize: from A, all possible directions
    for(int d=0;d<4;d++){
        int nx = ax + dx[d];
        int ny = ay + dy[d];
        if(nx >=0 && nx <N && ny >=0 && ny <N && grid[nx][ny] != 'x'){
            min_turns[nx][ny][d] = 0;
            Node node = {nx, ny, d, 0};
            pushQueue(pq, node);
        }
    }
    while(pq->size >0){
        Node current = popQueue(pq);
        if(current.x == bx && current.y == by){
            printf("%d\n", current.cost);
            // Free memory
            free(pq->data);
            free(pq);
            return 0;
        }
        if(current.cost > min_turns[current.x][current.y][current.dir]) continue;
        for(int nd=0;nd<4;nd++){
            int nx = current.x + dx[nd];
            int ny = current.y + dy[nd];
            if(nx >=0 && nx <N && ny >=0 && ny <N && grid[nx][ny] != 'x'){
                int ncost = current.cost;
                if(nd != current.dir){
                    ncost +=1;
                }
                if(ncost < min_turns[nx][ny][nd]){
                    min_turns[nx][ny][nd] = ncost;
                    Node next = {nx, ny, nd, ncost};
                    pushQueue(pq, next);
                }
            }
        }
    }
    // If not found
    printf("-1\n");
    free(pq->data);
    free(pq);
    return 0;
}
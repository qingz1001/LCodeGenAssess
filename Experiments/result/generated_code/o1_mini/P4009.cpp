#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 101
#define MAXK 11
#define INF 2147483647

typedef struct {
    int cost;
    int x;
    int y;
    int fuel;
} Node;

typedef struct {
    Node *data;
    int size;
    int capacity;
} MinHeap;

// Initialize the heap
MinHeap* createHeap(int capacity){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (Node*)malloc(sizeof(Node)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two nodes
void swap(Node* a, Node* b){
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Push a node into the heap
void pushHeap(MinHeap* heap, Node node){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (Node*)realloc(heap->data, sizeof(Node)*heap->capacity);
    }
    heap->data[heap->size] = node;
    int i = heap->size;
    heap->size++;
    while(i >0){
        int parent = (i-1)/2;
        if(heap->data[parent].cost > heap->data[i].cost){
            swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        }
        else break;
    }
}

// Pop the minimum node from the heap
Node popHeap(MinHeap* heap){
    Node min = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i =0;
    while(1){
        int left = 2*i+1;
        int right = 2*i+2;
        int smallest = i;
        if(left < heap->size && heap->data[left].cost < heap->data[smallest].cost){
            smallest = left;
        }
        if(right < heap->size && heap->data[right].cost < heap->data[smallest].cost){
            smallest = right;
        }
        if(smallest != i){
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return min;
}

int main(){
    int N, K, A, B, C;
    scanf("%d %d %d %d %d", &N, &K, &A, &B, &C);
    int grid[MAXN][MAXN];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    // Initialize DP table
    long long dp[MAXN][MAXN][MAXK];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            for(int f=0; f<=K; f++) {
                dp[i][j][f] = INF;
            }
        }
    }
    
    // Initialize heap
    MinHeap* heap = createHeap(100000);
    Node start;
    start.cost = 0;
    start.x =1;
    start.y =1;
    start.fuel = K;
    dp[1][1][K] =0;
    pushHeap(heap, start);
    
    // Directions: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    
    while(heap->size >0){
        Node current = popHeap(heap);
        int x = current.x;
        int y = current.y;
        int fuel = current.fuel;
        int cost = current.cost;
        if(x == N && y == N){
            // Found destination
            printf("%d", cost);
            return 0;
        }
        if(cost > dp[x][y][fuel]){
            continue;
        }
        // Explore all 4 directions
        for(int dir=0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if(nx <1 || nx >N || ny <1 || ny >N){
                continue;
            }
            if(fuel ==0){
                continue;
            }
            // Calculate movement cost
            int move_cost =0;
            if(nx < x || ny < y){
                move_cost = B;
            }
            // New fuel
            int nfuel = fuel -1;
            // At new node, decide to refill or not
            if(grid[nx][ny]){
                // Must refill, pay A
                int total_cost = cost + move_cost + A;
                if(total_cost < dp[nx][ny][K]){
                    dp[nx][ny][K] = total_cost;
                    Node next;
                    next.cost = total_cost;
                    next.x = nx;
                    next.y = ny;
                    next.fuel = K;
                    pushHeap(heap, next);
                }
            }
            else{
                // Option 1: do not refill
                if(cost + move_cost < dp[nx][ny][nfuel]){
                    dp[nx][ny][nfuel] = cost + move_cost;
                    Node next;
                    next.cost = cost + move_cost;
                    next.x = nx;
                    next.y = ny;
                    next.fuel = nfuel;
                    pushHeap(heap, next);
                }
                // Option 2: install depot, pay C + A and refill
                int total_cost = cost + move_cost + C + A;
                if(total_cost < dp[nx][ny][K]){
                    dp[nx][ny][K] = total_cost;
                    Node next;
                    next.cost = total_cost;
                    next.x = nx;
                    next.y = ny;
                    next.fuel = K;
                    pushHeap(heap, next);
                }
            }
        }
    }
    
    // Find the minimal cost at destination
    long long min_cost = INF;
    for(int f=0; f<=K; f++) {
        if(dp[N][N][f] < min_cost){
            min_cost = dp[N][N][f];
        }
    }
    printf("%lld", min_cost);
    return 0;
}
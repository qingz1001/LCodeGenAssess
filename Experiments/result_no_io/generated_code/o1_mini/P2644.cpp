#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 30
#define MAX_N 30
#define INF 1000000000
#define MAX_HEAP_SIZE 1000000

typedef long long ll;

typedef struct {
    int s;
    int g;
    int x;
    int y;
} HeapNode;

typedef struct {
    HeapNode data[MAX_HEAP_SIZE];
    int size;
} MinHeap;

// Initialize the heap
void initHeap(MinHeap* heap) {
    heap->size = 0;
}

// Compare two HeapNodes
int less(HeapNode a, HeapNode b) {
    if (a.s != b.s)
        return a.s < b.s;
    return a.g > b.g;
}

// Swap two HeapNodes
void swapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Push a node into the heap
void pushHeap(MinHeap* heap, HeapNode node) {
    if (heap->size >= MAX_HEAP_SIZE) return;
    int i = heap->size++;
    heap->data[i] = node;
    while (i != 0) {
        int parent = (i -1)/2;
        if (less(heap->data[i], heap->data[parent])) {
            swapNodes(&heap->data[i], &heap->data[parent]);
            i = parent;
        }
        else break;
    }
}

// Pop the top node from the heap
HeapNode popHeap(MinHeap* heap) {
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2*i +1;
        int right = 2*i +2;
        if (left < heap->size && less(heap->data[left], heap->data[smallest]))
            smallest = left;
        if (right < heap->size && less(heap->data[right], heap->data[smallest]))
            smallest = right;
        if (smallest != i) {
            swapNodes(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    int P, M, N;
    scanf("%d %d %d", &P, &M, &N);
    int grid[MAX_M][MAX_N];
    int start_x = -1, start_y = -1, end_x = -1, end_y = -1;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &grid[i][j]);
            if(grid[i][j] ==3){
                start_x = i;
                start_y = j;
            }
            if(grid[i][j]==4){
                end_x = i;
                end_y = j;
            }
        }
    }
    if(start_x==-1 || start_y==-1 || end_x==-1 || end_y==-1){
        printf("-1");
        return 0;
    }
    int dx[8] = {1,2,-1,-2,1,2,-1,-2};
    int dy[8] = {2,1,2,1,-2,-1,-2,-1};
    int min_S[MAX_M][MAX_N];
    ll W_S[MAX_M][MAX_N];
    int max_G[MAX_M][MAX_N];
    ll W_GV[MAX_M][MAX_N];
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            min_S[i][j] = INF;
            W_S[i][j] = 0;
            max_G[i][j] = -1;
            W_GV[i][j] = 0;
        }
    }
    min_S[start_x][start_y] =0;
    W_S[start_x][start_y] =1;
    max_G[start_x][start_y] =0;
    W_GV[start_x][start_y] =1;
    MinHeap heap;
    initHeap(&heap);
    HeapNode start_node = {0,0,start_x,start_y};
    pushHeap(&heap, start_node);
    while(heap.size >0){
        HeapNode current = popHeap(&heap);
        int x = current.x;
        int y = current.y;
        int s = current.s;
        int g = current.g;
        if(s > min_S[x][y]) continue;
        for(int dir=0; dir<8; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if(nx <0 || nx >=M || ny <0 || ny >=N) continue;
            if(grid[nx][ny]==2) continue;
            int cost=0;
            int g_inc=0;
            if(grid[nx][ny]==0){
                cost=1;
            }
            else if(grid[nx][ny]==1 || grid[nx][ny]==3 || grid[nx][ny]==4){
                cost=0;
            }
            else if(grid[nx][ny]==5){
                cost=2;
                g_inc=1;
            }
            int s_new = s + cost;
            int g_new = g + g_inc;
            if(s_new < min_S[nx][ny]){
                min_S[nx][ny] = s_new;
                W_S[nx][ny] = W_S[x][y];
                max_G[nx][ny] = g_new;
                W_GV[nx][ny] = W_GV[x][y];
                HeapNode new_node = {s_new, g_new, nx, ny};
                pushHeap(&heap, new_node);
            }
            else if(s_new == min_S[nx][ny]){
                W_S[nx][ny] += W_S[x][y];
                if(g_new > max_G[nx][ny]){
                    max_G[nx][ny] = g_new;
                    W_GV[nx][ny] = W_GV[x][y];
                }
                else if(g_new == max_G[nx][ny]){
                    W_GV[nx][ny] += W_GV[x][y];
                }
            }
        }
    }
    int end_S = min_S[end_x][end_y];
    if(end_S > P){
        printf("-1");
        return 0;
    }
    printf("%d %lld\n", end_S, W_S[end_x][end_y]);
    if(max_G[end_x][end_y] >0){
        printf("%d %lld", max_G[end_x][end_y], W_GV[end_x][end_y]);
    }
    else{
        printf("-1");
    }
    return 0;
}
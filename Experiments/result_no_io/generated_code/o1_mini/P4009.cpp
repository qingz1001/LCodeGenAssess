#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    ll cost;
    int x;
    int y;
    int f;
} State;

typedef struct {
    State* data;
    int size;
    int capacity;
} Heap;

void heap_init(Heap* heap, int capacity){
    heap->data = (State*)malloc(sizeof(State)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
}

void heap_swap(State* a, State* b){
    State temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(Heap* heap, State s){
    if(heap->size == heap->capacity){
        heap->capacity *=2;
        heap->data = (State*)realloc(heap->data, sizeof(State)*heap->capacity);
    }
    heap->data[heap->size] = s;
    int i = heap->size;
    heap->size++;
    while(i > 0){
        int parent = (i-1)/2;
        if(heap->data[parent].cost > heap->data[i].cost){
            heap_swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        }
        else break;
    }
}

State heap_pop(Heap* heap){
    State top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while(1){
        int smallest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        if(left < heap->size && heap->data[left].cost < heap->data[smallest].cost){
            smallest = left;
        }
        if(right < heap->size && heap->data[right].cost < heap->data[smallest].cost){
            smallest = right;
        }
        if(smallest != i){
            heap_swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
        else break;
    }
    return top;
}

int main(){
    int N, K, A, B, C;
    scanf("%d %d %d %d %d", &N, &K, &A, &B, &C);
    int grid[101][101];
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            scanf("%d", &grid[i][j]);
        }
    }
    ll INF = 1LL<<60;
    ll cost_table[101][101][11];
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            for(int f=0; f<=K; f++)
                cost_table[i][j][f] = INF;
    cost_table[1][1][K] = 0;
    Heap heap;
    heap_init(&heap, 1000000);
    State start = {0, 1, 1, K};
    heap_push(&heap, start);
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while(heap.size > 0){
        State current = heap_pop(&heap);
        if(current.x == N && current.y == N){
            printf("%lld\n", current.cost);
            return 0;
        }
        if(current.cost > cost_table[current.x][current.y][current.f]){
            continue;
        }
        for(int dir=0; dir<4; dir++){
            int nx = current.x + dx[dir];
            int ny = current.y + dy[dir];
            if(nx <1 || nx > N || ny <1 || ny > N) continue;
            ll new_cost = current.cost;
            if(nx < current.x || ny < current.y){
                new_cost += B;
            }
            int new_f = current.f -1;
            if(new_f <0) continue;
            if(grid[nx][ny]){
                ll total_cost = new_cost + A;
                if(total_cost < cost_table[nx][ny][K]){
                    cost_table[nx][ny][K] = total_cost;
                    State s = {total_cost, nx, ny, K};
                    heap_push(&heap, s);
                }
            }
            else{
                // Option 1: Do not install
                if(new_cost < cost_table[nx][ny][new_f]){
                    cost_table[nx][ny][new_f] = new_cost;
                    State s1 = {new_cost, nx, ny, new_f};
                    heap_push(&heap, s1);
                }
                // Option 2: Install and refuel
                ll total_cost_install = new_cost + C + A;
                if(total_cost_install < cost_table[nx][ny][K]){
                    cost_table[nx][ny][K] = total_cost_install;
                    State s2 = {total_cost_install, nx, ny, K};
                    heap_push(&heap, s2);
                }
            }
        }
    }
    return 0;
}
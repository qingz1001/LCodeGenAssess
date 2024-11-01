#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101
#define MAXK 100
#define MAXM 10001
#define MAXQUEUE 1000000

typedef struct {
    int to;
    int d;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int cnt;
} AdjList;

typedef struct {
    int country;
    unsigned long long mask1;
    unsigned long long mask2;
    int dist;
} State;

typedef struct {
    State data[MAXQUEUE];
    int size;
} Heap;

void heap_init(Heap *h) {
    h->size = 0;
}

int heap_empty(Heap *h) {
    return h->size == 0;
}

void heap_push(Heap *h, State s) {
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[parent].dist <= s.dist) break;
        h->data[i] = h->data[parent];
        i = parent;
    }
    h->data[i] = s;
}

State heap_pop(Heap *h) {
    State top = h->data[0];
    State tmp = h->data[--h->size];
    int i = 0;
    while (i * 2 + 1 < h->size) {
        int left = i * 2 + 1, right = i * 2 + 2, smallest = left;
        if (right < h->size && h->data[right].dist < h->data[left].dist) smallest = right;
        if (tmp.dist <= h->data[smallest].dist) break;
        h->data[i] = h->data[smallest];
        i = smallest;
    }
    h->data[i] = tmp;
    return top;
}

AdjList adj[MAXN];
int C[MAXN];
int a[MAXK+1][MAXK+1];
int N,K,M,S,T;

int main(){
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);
    for(int i=1;i<=N;i++) scanf("%d", &C[i]);
    for(int i=1;i<=K;i++) {
        for(int j=1;j<=K;j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for(int i=0;i<M;i++){
        int u,v,d;
        scanf("%d %d %d", &u, &v, &d);
        adj[u].edges[adj[u].cnt].to = v;
        adj[u].edges[adj[u].cnt++].d = d;
        adj[v].edges[adj[v].cnt].to = u;
        adj[v].edges[adj[v].cnt++].d = d;
    }
    Heap heap;
    heap_init(&heap);
    State start;
    start.country = S;
    start.dist = 0;
    start.mask1 = 0;
    start.mask2 = 0;
    if(C[S] <= 64) start.mask1 |= 1ULL << (C[S]-1);
    else start.mask2 |= 1ULL << (C[S]-65);
    heap_push(&heap, start);
    // Visited array
    unsigned long long visited1[MAXN][2] = {0};
    unsigned long long visited2[MAXN][2] = {0};
    // Using bitmask hash with first two bits as a simple hash
    while(!heap_empty(&heap)){
        State current = heap_pop(&heap);
        if(current.country == T){
            printf("%d", current.dist);
            return 0;
        }
        // Simple visited check
        int idx = 0;
        if(C[current.country] <= 64){
            idx = 0;
        }
        else{
            idx = 1;
        }
        if(current.country >=1 && current.country <=N){
            if(C[current.country] <=64){
                if(visited1[current.country][idx] & (1ULL << (C[current.country]-1))) continue;
                visited1[current.country][idx] |= (1ULL << (C[current.country]-1));
            }
            else{
                if(visited2[current.country][idx] & (1ULL << (C[current.country]-65))) continue;
                visited2[current.country][idx] |= (1ULL << (C[current.country]-65));
            }
        }
        for(int i=0;i<adj[current.country].cnt;i++){
            int next = adj[current.country].edges[i].to;
            int d = adj[current.country].edges[i].d;
            // Check culture
            int c = C[next];
            int duplicate = 0;
            if(c <=64){
                if(current.mask1 & (1ULL << (c-1))) duplicate = 1;
            }
            else{
                if(current.mask2 & (1ULL << (c-65))) duplicate =1;
            }
            if(duplicate) continue;
            // Check rejection
            int reject = 0;
            for(int ck=1;ck<=K;ck++){
                int has = 0;
                if(ck <=64){
                    if(current.mask1 & (1ULL << (ck-1))) has =1;
                }
                else{
                    if(current.mask2 & (1ULL << (ck-65))) has =1;
                }
                if(has && a[ck][c]){
                    reject =1;
                    break;
                }
            }
            if(reject) continue;
            // Add to heap
            State next_state;
            next_state.country = next;
            next_state.dist = current.dist + d;
            next_state.mask1 = current.mask1;
            next_state.mask2 = current.mask2;
            if(c <=64){
                next_state.mask1 |= (1ULL << (c-1));
            }
            else{
                next_state.mask2 |= (1ULL << (c-65));
            }
            heap_push(&heap, next_state);
        }
    }
    printf("-1");
    return 0;
}
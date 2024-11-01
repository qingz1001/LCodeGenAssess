#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20005
#define MAX_M 200005
#define MAX_K 100005

typedef struct Zombie {
    int X;
} Zombie;

typedef struct Track {
    Zombie *zombies;
    int size;
    int capacity;
} Track;

typedef struct HeapNode {
    int kill;
    int track;
    int idx;
} HeapNode;

HeapNode heap[MAX_N];
int heap_size = 0;

Track tracks[MAX_N];
int total_kills = 0;

// Comparator for max heap
int cmp(const HeapNode a, const HeapNode b){
    if(a.kill != b.kill) return a.kill > b.kill ? 1 : -1;
    return a.track < b.track ? 1 : -1;
}

void swap(HeapNode *a, HeapNode *b){
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(HeapNode node){
    heap[heap_size] = node;
    int i = heap_size;
    heap_size++;
    while(i > 0){
        int parent = (i-1)/2;
        if(cmp(heap[i], heap[parent]) > 0){
            swap(&heap[i], &heap[parent]);
            i = parent;
        }
        else break;
    }
}

HeapNode heap_pop(){
    HeapNode top = heap[0];
    heap_size--;
    heap[0] = heap[heap_size];
    int i = 0;
    while(1){
        int left = 2*i+1, right = 2*i+2, largest = i;
        if(left < heap_size && cmp(heap[left], heap[largest]) > 0) largest = left;
        if(right < heap_size && cmp(heap[right], heap[largest]) > 0) largest = right;
        if(largest != i){
            swap(&heap[i], &heap[largest]);
            i = largest;
        }
        else break;
    }
    return top;
}

int compare(const void *a, const void *b){
    Zombie *za = (Zombie *)a;
    Zombie *zb = (Zombie *)b;
    return za->X - zb->X;
}

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    for(int i=1;i<=N;i++){
        tracks[i].zombies = malloc(sizeof(Zombie)*2);
        tracks[i].size = 0;
        tracks[i].capacity =2;
    }
    int X, Y;
    for(int i=0;i<M;i++){
        scanf("%d %d", &X, &Y);
        if(tracks[Y].size == tracks[Y].capacity){
            tracks[Y].capacity *=2;
            tracks[Y].zombies = realloc(tracks[Y].zombies, sizeof(Zombie)*tracks[Y].capacity);
        }
        tracks[Y].zombies[tracks[Y].size].X = X;
        tracks[Y].size++;
    }
    for(int i=1;i<=N;i++) {
        qsort(tracks[i].zombies, tracks[i].size, sizeof(Zombie), compare);
    }
    // Initialize kill counts
    for(int i=1;i<=N;i++){
        // Simplistic kill count: all zombies on the track
        HeapNode node;
        node.kill = tracks[i].size;
        node.track = i;
        node.idx = 0;
        heap_push(node);
    }
    // Process K rounds
    for(int round=0; round<K; round++){
        if(heap_size ==0){
            printf("1 0\n");
            continue;
        }
        HeapNode top = heap_pop();
        int track = top.track;
        int kills = top.kill;
        if(kills ==0){
            printf("1 0\n");
            continue;
        }
        printf("%d %d\n", track, kills);
        total_kills += kills;
        // Remove all zombies from this track
        tracks[track].size =0;
        // Push updated kill count
        HeapNode newnode;
        newnode.kill =0;
        newnode.track = track;
        newnode.idx =0;
        heap_push(newnode);
    }
    printf("%d\n", total_kills);
    // Free memory
    for(int i=1;i<=N;i++) free(tracks[i].zombies);
    return 0;
}
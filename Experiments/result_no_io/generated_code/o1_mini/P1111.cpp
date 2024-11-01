#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int t;
} Road;

int compare(const void *a, const void *b) {
    Road *ra = (Road *)a;
    Road *rb = (Road *)b;
    if (ra->t != rb->t)
        return ra->t - rb->t;
    return 0;
}

int parent[1001];
int rank_set[1001];

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx == fy)
        return 0;
    if (rank_set[fx] < rank_set[fy]) {
        parent[fx] = fy;
    }
    else {
        parent[fy] = fx;
        if (rank_set[fx] == rank_set[fy])
            rank_set[fx]++;
    }
    return 1;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Road *roads = (Road*)malloc(sizeof(Road)*M);
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &roads[i].x, &roads[i].y, &roads[i].t);
    }
    if(N == 1){
        printf("0");
        free(roads);
        return 0;
    }
    qsort(roads, M, sizeof(Road), compare);
    for(int i=1;i<=N;i++){
        parent[i] = i;
        rank_set[i] = 0;
    }
    int components = N;
    int answer = -1;
    for(int i=0;i<M;i++){
        if(union_set(roads[i].x, roads[i].y)){
            components--;
            if(components == 1){
                answer = roads[i].t;
                break;
            }
        }
    }
    printf("%d", answer);
    free(roads);
    return 0;
}
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

int find_set(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent, parent[x]);
    return parent[x];
}

int main(){
    int N, M;
    if(scanf("%d %d", &N, &M)!=2){
        return 0;
    }

    if(N ==1){
        printf("0\n");
        return 0;
    }

    Road *roads = (Road *)malloc(sizeof(Road)*M);
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &roads[i].x, &roads[i].y, &roads[i].t);
    }

    qsort(roads, M, sizeof(Road), compare);

    int *parent = (int *)malloc(sizeof(int)*(N+1));
    for(int i=1;i<=N;i++) parent[i] = i;

    int components = N;
    int result = -1;
    for(int i=0;i<M;i++){
        int fx = find_set(parent, roads[i].x);
        int fy = find_set(parent, roads[i].y);
        if(fx != fy){
            parent[fx] = fy;
            components--;
            if(components ==1){
                result = roads[i].t;
                break;
            }
        }
    }

    if(result == -1){
        printf("-1\n");
    }
    else{
        printf("%d\n", result);
    }

    free(roads);
    free(parent);
    return 0;
}
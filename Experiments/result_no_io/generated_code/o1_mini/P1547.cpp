#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    long long l;
} Edge;

int cmp(const void *x, const void *y) {
    Edge *e1 = (Edge *)x;
    Edge *e2 = (Edge *)y;
    if (e1->l < e2->l) return -1;
    if (e1->l > e2->l) return 1;
    return 0;
}

long long parent[2001];
int rank_set[2001];

long long find_set(long long x){
    if(parent[x] != x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void union_set(long long x, long long y){
    long long fx = find_set(x);
    long long fy = find_set(y);
    if(fx != fy){
        if(rank_set[fx] < rank_set[fy]){
            parent[fx] = fy;
        }
        else{
            parent[fy] = fx;
            if(rank_set[fx] == rank_set[fy]){
                rank_set[fx]++;
            }
        }
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Edge *edges = (Edge *)malloc(M * sizeof(Edge));
    for(int i = 0; i < M; i++){
        scanf("%d %d %lld", &edges[i].a, &edges[i].b, &edges[i].l);
    }
    qsort(edges, M, sizeof(Edge), cmp);
    for(int i = 1; i <= N; i++){
        parent[i] = i;
        rank_set[i] = 0;
    }
    long long max_edge = 0;
    int count = 0;
    for(int i = 0; i < M && count < N-1; i++){
        if(find_set(edges[i].a) != find_set(edges[i].b)){
            union_set(edges[i].a, edges[i].b);
            if(edges[i].l > max_edge){
                max_edge = edges[i].l;
            }
            count++;
        }
    }
    printf("%lld\n", max_edge);
    free(edges);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
    int l;
} Edge;

int cmp(const void *x, const void *y) {
    Edge *e1 = (Edge *)x;
    Edge *e2 = (Edge *)y;
    if (e1->l != e2->l)
        return e1->l - e2->l;
    return 0;
}

int parent[2005];
int rank_arr[2005];

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx == fy)
        return;
    if (rank_arr[fx] < rank_arr[fy]) {
        parent[fx] = fy;
    }
    else {
        parent[fy] = fx;
        if (rank_arr[fx] == rank_arr[fy])
            rank_arr[fx]++;
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Edge edges[10005];
    for(int i=0;i<M;i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].l);
    }
    qsort(edges, M, sizeof(Edge), cmp);
    for(int i=1;i<=N;i++) {
        parent[i] = i;
        rank_arr[i] = 0;
    }
    int count = 0;
    int max_edge = 0;
    for(int i=0;i<M && count < N-1;i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        int l = edges[i].l;
        if(find_set(a) != find_set(b)){
            union_set(a, b);
            if(l > max_edge)
                max_edge = l;
            count++;
        }
    }
    printf("%d\n", max_edge);
    return 0;
}
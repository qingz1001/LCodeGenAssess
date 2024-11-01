#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int Ti;
    int ti;
} Edge;

typedef struct {
    int parent;
    int rank;
} UFNode;

int cmp_boy_first(const void *a, const void *b, void *x_ptr) {
    int X = *(int*)x_ptr;
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    int a_boy = (ea->Ti <= X) ? 1 : 0;
    int b_boy = (eb->Ti <= X) ? 1 : 0;
    if (a_boy != b_boy) return b_boy - a_boy;
    return 0;
}

int find_set(UFNode *uf, int x) {
    if (uf[x].parent != x)
        uf[x].parent = find_set(uf, uf[x].parent);
    return uf[x].parent;
}

void union_set(UFNode *uf, int x, int y) {
    int fx = find_set(uf, x);
    int fy = find_set(uf, y);
    if (fx == fy) return;
    if (uf[fx].rank < uf[fy].rank) {
        uf[fx].parent = fy;
    }
    else {
        uf[fy].parent = fx;
        if (uf[fx].rank == uf[fy].rank)
            uf[fx].rank++;
    }
}

int feasible(Edge *edges, int m, int n, int k, int X) {
    UFNode *uf = (UFNode*)malloc((n+1) * sizeof(UFNode));
    for(int i=1;i<=n;i++) {
        uf[i].parent = i;
        uf[i].rank = 0;
    }
    // Sort edges with 'boy' edges first
    qsort_r(edges, m, sizeof(Edge), cmp_boy_first, &X);
    int count_boy = 0, count = 0;
    for(int i=0;i<m;i++) {
        if ((edges[i].Ti <= X) || (edges[i].ti <= X)) {
            int type_boy = (edges[i].Ti <= X);
            int fa = find_set(uf, edges[i].a);
            int fb = find_set(uf, edges[i].b);
            if (fa != fb) {
                union_set(uf, fa, fb);
                count++;
                if (type_boy) count_boy++;
                if (count == n-1) break;
            }
        }
    }
    free(uf);
    if (count == n-1 && count_boy >= k)
        return 1;
    return 0;
}

int main(){
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    Edge *edges = (Edge*)malloc(m * sizeof(Edge));
    for(int i=0;i<m;i++) {
        scanf("%d %d %d %d", &edges[i].a, &edges[i].b, &edges[i].Ti, &edges[i].ti);
    }
    int lo = 1, hi = 1000000, ans = hi;
    while(lo <= hi){
        int mid = lo + (hi - lo)/2;
        if(feasible(edges, m, n, k, mid)){
            ans = mid;
            hi = mid -1;
        }
        else{
            lo = mid +1;
        }
    }
    printf("%d\n", ans);
    free(edges);
    return 0;
}
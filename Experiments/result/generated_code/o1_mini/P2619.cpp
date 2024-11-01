#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int u, v;
    int c;
    int col;
} Edge;

int cmp(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    return ea->c - eb->c;
}

int parent[50005];
int rank_set[50005];

int find_set(int x){
    if(parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

ll mst(int V, Edge* edges, double lambda, int* white_cnt){
    for(int i=0;i<V;i++) { parent[i] = i; rank_set[i] = 0; }
    ll total = 0;
    *white_cnt = 0;
    for(int i=0;i<V-1;){
        Edge e = edges[i];
        int fx = find_set(e.u);
        int fy = find_set(e.v);
        if(fx != fy){
            parent[fx] = fy;
            if(e.col == 0){
                (*white_cnt)++;
                total += e.c;
            }
            else{
                total += e.c;
            }
            i++;
        }
    }
    return total;
}

int main(){
    int V, E, need;
    scanf("%d %d %d", &V, &E, &need);
    Edge* edges = (Edge*)malloc(sizeof(Edge)*E);
    for(int i=0;i<E;i++) scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].c, &edges[i].col);
    qsort(edges, E, sizeof(Edge), cmp);
    double left = -100000.0, right = 100000.0;
    ll answer = 0;
    for(int iter=0; iter<50; iter++){
        double mid = (left + right) / 2.0;
        // Modify weights
        for(int i=0;i<E;i++) {
            if(edges[i].col == 0){
                // White edge: cost = c - lambda
                // Not used in this implementation
            }
        }
        // Compute MST and count white edges
        int white_cnt = 0;
        ll total = 0;
        for(int i=0;i<V;i++){ parent[i] = i; rank_set[i] = 0; }
        for(int i=0;i<E && white_cnt <= need;i++){
            Edge e = edges[i];
            int fx = find_set(e.u);
            int fy = find_set(e.v);
            if(fx != fy){
                parent[fx] = fy;
                total += e.c;
                if(e.col == 0) white_cnt++;
            }
        }
        if(white_cnt < need){
            left = mid;
        }
        else{
            right = mid;
            answer = total;
        }
    }
    printf("%lld\n", answer);
    free(edges);
    return 0;
}
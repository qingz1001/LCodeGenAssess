#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int l;
} Edge;

int cmp(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->l != eb->l)
        return ea->l - eb->l;
    return 0;
}

int parent_array[1001];

int find_set(int a) {
    if (parent_array[a] != a)
        parent_array[a] = find_set(parent_array[a]);
    return parent_array[a];
}

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    
    if(K > N){
        printf("No Answer\n");
        return 0;
    }
    
    Edge edges[10000];
    for(int i=0;i<M;i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].l);
    }
    
    qsort(edges, M, sizeof(Edge), cmp);
    
    for(int i=1;i<=N;i++) parent_array[i] = i;
    
    int components = N;
    long long sum = 0;
    for(int i=0;i<M && components > K;i++) {
        int fx = find_set(edges[i].x);
        int fy = find_set(edges[i].y);
        if(fx != fy){
            parent_array[fx] = fy;
            sum += edges[i].l;
            components--;
        }
    }
    
    if(components == K){
        printf("%lld\n", sum);
    }
    else{
        printf("No Answer\n");
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 300005

typedef struct {
    int parent;
    int rank;
} UF;

UF uf[MAX];
int N, M, Q;

// Find with path compression
int find_set(int x){
    if(uf[x].parent != x){
        uf[x].parent = find_set(uf[x].parent);
    }
    return uf[x].parent;
}

// Union by rank
void union_set(int x, int y){
    int fx = find_set(x);
    int fy = find_set(y);
    if(fx == fy) return;
    if(uf[fx].rank < uf[fy].rank){
        uf[fx].parent = fy;
    }
    else{
        uf[fy].parent = fx;
        if(uf[fx].rank == uf[fy].rank){
            uf[fx].rank++;
        }
    }
}

int main(){
    // Read N and M
    if(scanf("%d %d", &N, &M)!=2) return 0;
    // Initialize UF
    for(int i=1;i<=N;i++){
        uf[i].parent = i;
        uf[i].rank = 0;
    }
    // Read M edges
    for(int i=0;i<M;i++){
        int X, Y, Z;
        if(scanf("%d %d %d", &X, &Y, &Z)!=3) return 0;
        if(Z == 0){
            union_set(X, Y);
        }
    }
    // Read Q
    if(scanf("%d", &Q)!=1) return 0;
    // Process Q queries
    for(int i=0;i<Q;i++){
        int S, T;
        if(scanf("%d %d", &S, &T)!=2) return 0;
        if(find_set(S) != find_set(T)){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
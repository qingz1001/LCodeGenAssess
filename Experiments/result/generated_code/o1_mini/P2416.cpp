#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

int parent[MAXN];

int find_set(int x){
    if(parent[x] != x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) parent[i] = i;
    int X, Y, Z;
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &X, &Y, &Z);
        if(Z == 0){
            int fx = find_set(X);
            int fy = find_set(Y);
            if(fx != fy){
                parent[fx] = fy;
            }
        }
    }
    int Q;
    scanf("%d", &Q);
    while(Q--){
        int S, T;
        scanf("%d %d", &S, &T);
        if(find_set(S) == find_set(T)){
            printf("NO\n");
        }
        else{
            printf("YES\n");
        }
    }
    return 0;
}
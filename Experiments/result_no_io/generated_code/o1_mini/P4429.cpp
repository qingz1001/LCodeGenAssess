#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10001

int parent[MAX_N];

int find_set(int x){
    if(parent[x] != x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

int main(){
    int T;
    if(scanf("%d", &T)!=1) return 0;
    while(T--){
        int n, m;
        if(scanf("%d %d", &n, &m)!=2) return 0;
        for(int i =1;i<=n;i++) parent[i] = i;
        int is_forest = 1;
        for(int i=0;i<m;i++){
            int u, v;
            if(scanf("%d %d", &u, &v)!=2) return 0;
            int pu = find_set(u);
            int pv = find_set(v);
            if(pu == pv){
                is_forest = 0;
            }
            else{
                parent[pu] = pv;
            }
        }
        if(is_forest){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
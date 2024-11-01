#include <stdio.h>
#include <stdlib.h>

#define MAX 1001
#define INF 10000

int adj[MAX][MAX];
int num_children[MAX];
int base_count = 0;

int dfs(int node, int parent){
    int min_distance = INF;
    for(int i=0; i<num_children[node]; i++){
        int child = adj[node][i];
        if(child == parent) continue;
        int child_distance = dfs(child, node);
        if(child_distance +1 < min_distance){
            min_distance = child_distance +1;
        }
    }
    if(min_distance > 2){
        base_count++;
        return 0;
    }
    else{
        return min_distance;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=2; i<=n; i++){
        int a;
        scanf("%d", &a);
        adj[i][num_children[i]++] = a;
        adj[a][num_children[a]++] = i;
    }
    int root_distance = dfs(1, -1);
    if(root_distance >2){
        base_count++;
    }
    printf("%d\n", base_count);
    return 0;
}
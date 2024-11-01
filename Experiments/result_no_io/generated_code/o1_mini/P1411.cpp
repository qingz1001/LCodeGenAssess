#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 701
typedef unsigned long long ull;

// Adjacency list
int adj[MAXN][MAXN];
int adj_size[MAXN];

// DP table
ull dp_table[MAXN][MAXN];
int size_tree[MAXN];

int max(int a, int b){
    return a > b ? a : b;
}

void dfs(int u, int parent){
    size_tree[u] = 1;
    memset(dp_table[u], 0, sizeof(ull) * MAXN);
    dp_table[u][1] = 1;

    for(int i=0;i<adj_size[u];i++){
        int v = adj[u][i];
        if(v == parent) continue;
        dfs(v, u);

        // Temporary array
        ull tmp[MAXN];
        memset(tmp, 0, sizeof(tmp));

        for(int k1=1; k1 <= size_tree[u]; k1++){
            if(dp_table[u][k1] == 0) continue;

            // Option 1: keep connected
            int newS = k1 + size_tree[v];
            if(newS < MAXN){
                if(dp_table[u][k1] > tmp[newS]){
                    tmp[newS] = dp_table[u][k1];
                }
            }

            // Option 2: separate
            ull newP = dp_table[u][k1] * dp_table[v][size_tree[v]];
            if(newP > tmp[k1]){
                tmp[k1] = newP;
            }
        }

        // Update dp_table[u]
        for(int k=1; k <= size_tree[u] + size_tree[v]; k++){
            if(tmp[k] > dp_table[u][k]){
                dp_table[u][k] = tmp[k];
            }
        }

        // Update size
        size_tree[u] += size_tree[v];
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n-1;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][adj_size[u]++] = v;
        adj[v][adj_size[v]++] = u;
    }

    dfs(1, -1);

    ull max_product = 0;
    for(int k=1; k <= size_tree[1]; k++){
        ull current = dp_table[1][k] * k;
        if(current > max_product){
            max_product = current;
        }
    }

    printf("%llu\n", max_product);
    return 0;
}
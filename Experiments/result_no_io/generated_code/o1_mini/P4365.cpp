#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 64123
#define MAXN 1005

typedef struct Node {
    int id;
    int d;
} Node;

int cmp(const void* a, const void* b){
    Node *n1 = (Node*)a;
    Node *n2 = (Node*)b;
    if(n2->d != n1->d) return n2->d - n1->d;
    return n1->id - n2->id;
}

int n, k, W;
int d_val[MAXN];
int adj[MAXN][MAXN];
int dp[MAXN][MAXN];
long long result = 0;

void dfs(int u, int parent_u, Node nodes[], int* size){
    nodes[(*size)++] = (Node){u, d_val[u]};
    for(int i = 0; i < adj[u][0]; i++){
        int v = adj[u][i+1];
        if(v != parent_u){
            dfs(v, u, nodes, size);
        }
    }
}

int main(){
    scanf("%d %d %d", &n, &k, &W);
    for(int i=1;i<=n;i++) scanf("%d", &d_val[i]);
    for(int i=0;i<n-1;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x][0]++;
        adj[x][adj[x][0]] = y;
        adj[y][0]++;
        adj[y][adj[y][0]] = x;
    }

    // Sort nodes by d descending
    Node nodes_list[MAXN];
    for(int i=1;i<=n;i++) {nodes_list[i-1].id = i; nodes_list[i-1].d = d_val[i];}
    qsort(nodes_list, n, sizeof(Node), cmp);

    // Initialize dp
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<n;i++){
        int u = nodes_list[i].id;
        dp[u][1] = 1;
        for(int j=1; j<=n; j++){
            if(dp[u][j]){
                // Traverse neighbors
                for(int l=1;l<=adj[u][0];l++){
                    int v = adj[u][l];
                    if(d_val[v] < d_val[u]){
                        for(int m=1; m + j <=n; m++){
                            dp[u][j+m] = (dp[u][j+m] + dp[u][j] * dp[v][m]) % MOD;
                        }
                    }
                }
            }
        }
        if(k <= n){
            result = (result + ((long long)nodes_list[i].d * dp[u][k]) % MOD) % MOD;
        }
    }

    printf("%lld\n", result % MOD);
    return 0;
}
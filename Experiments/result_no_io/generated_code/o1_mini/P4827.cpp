#include <stdio.h>
#include <stdlib.h>
#define MOD 10007
#define MAXN 50005
#define MAXK 151

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* adj[MAXN];
long long dp[MAXN][MAXK];
long long up[MAXN][MAXK];
int n, k;

// Function to add edge
void addEdge(int u, int v){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->id = u;
    newNode->next = adj[v];
    adj[v] = newNode;
}

// Fast exponentiation for polynomials
void combine(long long a[], long long b[], long long res[]){
    for(int i=0;i<=k;i++) res[i] = 0;
    for(int i=0;i<=k;i++) {
        for(int j=0; j<=k-i; j++) {
            res[i+j] = (res[i+j] + a[i] * b[j]) % MOD;
        }
    }
}

// Post-order DP
void dfs1(int u, int parentu){
    dp[u][0] = 1;
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->id;
        if(v != parentu){
            dfs1(v, u);
            // Shift dp[v] by 1
            long long temp[MAXK] = {0};
            for(int i=0;i<=k-1;i++) {
                temp[i+1] = dp[v][i];
            }
            // Combine with dp[u]
            for(int i=0;i<=k;i++) {
                dp[u][i] = (dp[u][i] + temp[i]) % MOD;
            }
        }
        ptr = ptr->next;
    }
}

// Pre-order DP
void dfs2(int u, int parentu){
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->id;
        if(v != parentu){
            // Compute up[v]
            // up[v][d] = up[u][d-1] shifted + (dp[u][d-1] - dp[v][d-2])
            for(int d=0; d<=k; d++) {
                up[v][d] = 0;
                if(d > 0){
                    up[v][d] = up[u][d-1];
                }
                if(d >1){
                    up[v][d] = (up[v][d] + dp[u][d-1] - dp[v][d-2] + MOD) % MOD;
                }
            }
            dfs2(v, u);
        }
        ptr = ptr->next;
    }
}

long long power_table[MAXK];

int main(){
    scanf("%d %d", &n, &k);
    for(int i=0; i<n-1;i++){
        int u,v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    // Precompute powers
    power_table[0] = 1;
    for(int i=1;i<=k;i++) power_table[i] = (power_table[i-1] * i) % MOD;
    // Initialize
    dfs1(1, -1);
    // Initialize up for root
    for(int d=0; d<=k; d++) up[1][d] = 0;
    dfs2(1, -1);
    // Compute S(i)
    for(int u=1; u<=n; u++){
        long long S = 0;
        for(int d=0; d<=k; d++){
            S = (S + dp[u][d] * power_table[d]) % MOD;
            S = (S + up[u][d] * power_table[d]) % MOD;
        }
        printf("%lld\n", S);
    }
    return 0;
}
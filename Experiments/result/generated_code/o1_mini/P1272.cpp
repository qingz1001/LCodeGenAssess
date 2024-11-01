#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 151
#define INF 1000000

int N, P;
int parent_node[MAXN];
int children[MAXN][MAXN];
int child_count[MAXN];
int dp[MAXN][MAXN];

void dfs(int u) {
    if (child_count[u] == 0) {
        memset(dp[u], 0x3f, sizeof(dp[u]));
        dp[u][1] = 0;
        return;
    }

    memset(dp[u], 0x3f, sizeof(dp[u]));
    // Initialize with taking only u and cutting all its children
    dp[u][1] = child_count[u];

    for(int i = 0; i < child_count[u]; i++) {
        int c = children[u][i];
        dfs(c);
        int tmp[MAXN];
        for(int k = 0; k <= N; k++) tmp[k] = INF;
        for(int s = 1; s <= N; s++) {
            if(dp[u][s] < INF) {
                // Option 1: Exclude child c
                if(s <= N && dp[u][s] + 1 < tmp[s]) {
                    tmp[s] = dp[u][s] + 1;
                }
                // Option 2: Include child c with size sc
                for(int sc = 1; sc <= N - s; sc++) {
                    if(dp[c][sc] < INF && s + sc <= N) {
                        if(dp[u][s] + dp[c][sc] < tmp[s + sc]) {
                            tmp[s + sc] = dp[u][s] + dp[c][sc];
                        }
                    }
                }
            }
        }
        // Update dp[u][*] with tmp
        for(int k = 1; k <= N; k++) {
            dp[u][k] = tmp[k] < dp[u][k] ? tmp[k] : dp[u][k];
        }
    }
}

int main(){
    scanf("%d %d", &N, &P);
    for(int i = 0; i < N-1; i++) {
        int I, J;
        scanf("%d %d", &I, &J);
        children[J][child_count[J]++] = I;
    }

    dfs(1);

    int min_cuts = INF;
    for(int u = 1; u <= N; u++) {
        if(P == N && u == 1){
            if(dp[u][P] < min_cuts){
                min_cuts = dp[u][P];
            }
            continue;
        }
        if(dp[u][P] < INF){
            if(u == 1){
                if(dp[u][P] < min_cuts){
                    min_cuts = dp[u][P];
                }
            }
            else{
                if(dp[u][P] + 1 < min_cuts){
                    min_cuts = dp[u][P] + 1;
                }
            }
        }
    }

    printf("%d\n", min_cuts);
    return 0;
}
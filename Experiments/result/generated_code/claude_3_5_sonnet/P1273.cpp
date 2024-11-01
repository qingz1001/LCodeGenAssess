#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 3000
#define MAX_K 3000

struct Node {
    int id;
    int cost;
};

struct Station {
    int k;
    struct Node nodes[MAX_K];
};

struct Station stations[MAX_N];
int user_fees[MAX_N];
int dp[MAX_N][MAX_N];
int N, M;

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int station, int parent) {
    int i, j, k;
    
    for (i = 0; i < stations[station].k; i++) {
        int child = stations[station].nodes[i].id;
        if (child == parent) continue;
        
        if (child > N - M) {
            dp[station][1] = max(dp[station][1], user_fees[child] - stations[station].nodes[i].cost);
        } else {
            dfs(child, station);
            for (j = M; j >= 1; j--) {
                for (k = 0; k < j; k++) {
                    dp[station][j] = max(dp[station][j], 
                                         dp[station][j-k] + dp[child][k] - stations[station].nodes[i].cost);
                }
            }
        }
    }
    
    for (i = M; i >= 1; i--) {
        if (dp[station][i] >= 0) {
            dp[station][0] = i;
            break;
        }
    }
}

int main() {
    int i, j, k, a, c;
    
    scanf("%d %d", &N, &M);
    
    for (i = 1; i < N - M; i++) {
        scanf("%d", &stations[i].k);
        for (j = 0; j < stations[i].k; j++) {
            scanf("%d %d", &a, &c);
            stations[i].nodes[j].id = a;
            stations[i].nodes[j].cost = c;
        }
    }
    
    for (i = N - M + 1; i <= N; i++) {
        scanf("%d", &user_fees[i]);
    }
    
    memset(dp, -1, sizeof(dp));
    for (i = 0; i <= N; i++) {
        dp[i][0] = 0;
    }
    
    dfs(1, 0);
    
    printf("%d\n", dp[1][0]);
    
    return 0;
}
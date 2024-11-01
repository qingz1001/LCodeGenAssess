#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 3000
#define MAX_K 10

struct Node {
    int children[MAX_K];
    int costs[MAX_K];
    int child_count;
};

struct Node nodes[MAX_N];
int user_pay[MAX_N];
int dp[MAX_N][MAX_N];
int N, M;

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int node, int budget) {
    if (dp[node][budget] != -1) return dp[node][budget];
    
    if (node > N - M) {
        return dp[node][budget] = (budget >= 0) ? 1 : 0;
    }
    
    int result = 0;
    for (int mask = 0; mask < (1 << nodes[node].child_count); mask++) {
        int current_budget = budget;
        int current_result = 0;
        
        for (int i = 0; i < nodes[node].child_count; i++) {
            if (mask & (1 << i)) {
                current_budget -= nodes[node].costs[i];
                current_result += dfs(nodes[node].children[i], current_budget);
            }
        }
        
        if (current_budget >= 0) {
            result = max(result, current_result);
        }
    }
    
    return dp[node][budget] = result;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= N - M; i++) {
        int K;
        scanf("%d", &K);
        nodes[i].child_count = K;
        for (int j = 0; j < K; j++) {
            scanf("%d %d", &nodes[i].children[j], &nodes[i].costs[j]);
        }
    }
    
    int total_pay = 0;
    for (int i = N - M + 1; i <= N; i++) {
        scanf("%d", &user_pay[i]);
        total_pay += user_pay[i];
    }
    
    memset(dp, -1, sizeof(dp));
    
    printf("%d\n", dfs(1, total_pay));
    
    return 0;
}
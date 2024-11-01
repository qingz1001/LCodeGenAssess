#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 3005
#define MAXM 3005
#define INF 1000000000

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int N, M;
int payments[MAXN];
long long prefix_sum[MAXM];
int temp_dp1[MAXM];
int temp_dp2[MAXM];

void add_edge(int from, int to, int cost){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->cost = cost;
    e->next = adj[from];
    adj[from] = e;
}

void dfs(int u, int *dp){
    if(u > N - M){
        for(int i=0;i<=M;i++) dp[i] = INF;
        dp[0] = 0;
        dp[1] = 0; // Will add path cost later
        return;
    }
    // Initialize dp
    for(int i=0;i<=M;i++) dp[i] = INF;
    dp[0] = 0;
    // Iterate over children
    Edge* e = adj[u];
    while(e != NULL){
        int child = e->to;
        int edge_cost = e->cost;
        int child_dp[MAXM];
        dfs(child, child_dp);
        // Add edge cost to child's dp
        for(int i=0;i<=M;i++){
            if(child_dp[i] < INF){
                child_dp[i] += edge_cost;
            }
        }
        // Merge dp and child_dp
        memset(temp_dp1, 0, sizeof(temp_dp1));
        for(int i=0;i<=M;i++) temp_dp1[i] = dp[i];
        memset(temp_dp2, 0, sizeof(temp_dp2));
        for(int i=0;i<=M;i++) temp_dp2[i] = INF;
        for(int i=0;i<=M;i++){
            if(temp_dp1[i] < INF){
                for(int j=0; j<=M-i; j++){
                    if(child_dp[j] < INF){
                        if(temp_dp2[i+j] > temp_dp1[i] + child_dp[j]){
                            temp_dp2[i+j] = temp_dp1[i] + child_dp[j];
                        }
                    }
                }
            }
        }
        for(int i=0;i<=M;i++) dp[i] = temp_dp2[i];
        e = e->next;
    }
    return;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N-M;i++){
        int K;
        scanf("%d", &K);
        for(int j=0; j<K; j++){
            int A, C;
            scanf("%d %d", &A, &C);
            add_edge(i, A, C);
        }
    }
    for(int i=N-M+1;i<=N;i++) scanf("%d", &payments[i]);
    // Perform DFS from root
    int dp[MAXM];
    dfs(1, dp);
    // Collect all min_cost for k users
    // To get min_cost[k], need to consider selecting k users from the tree
    // Here dp[k] holds the total transmission cost for selecting k users
    // Now, sort payments in descending order
    int user_payments[M];
    for(int i=0;i<M;i++) user_payments[i] = payments[N-M+1+i];
    // Sort in descending order
    for(int i=0;i<M-1;i++) {
        for(int j=i+1;j<M;j++) {
            if(user_payments[i] < user_payments[j]){
                int tmp = user_payments[i];
                user_payments[i] = user_payments[j];
                user_payments[j] = tmp;
            }
        }
    }
    // Compute prefix sums
    prefix_sum[0] = 0;
    for(int i=1;i<=M;i++) prefix_sum[i] = prefix_sum[i-1] + user_payments[i-1];
    // Find the maximum k
    int result = 0;
    for(int k=1;k<=M;k++) {
        if(dp[k] <= prefix_sum[k]){
            result = k;
        }
    }
    printf("%d\n", result);
    return 0;
}
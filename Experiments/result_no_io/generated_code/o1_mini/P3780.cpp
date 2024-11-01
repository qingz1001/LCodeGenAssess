#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20005
#define MAX_K 500005
#define INF 0x3f3f3f3f

typedef long long ll;

int Q;
int n, k;
int parents[MAX_N];
ll a[MAX_N];
int v[MAX_N];
int depth_node[MAX_N];
int max_depth;
int children[MAX_N][200];
int child_cnt[MAX_N];
ll dp[MAX_K];
ll tmp_dp[MAX_K];

int main(){
    scanf("%d", &Q);
    while(Q--){
        scanf("%d %d", &n, &k);
        // Initialize
        for(int i=1;i<=n;i++){
            child_cnt[i]=0;
        }
        max_depth =1;
        for(int i=1;i<=n;i++){
            if(i==1){
                scanf("%d %lld %d", &parents[i], &a[i], &v[i]);
            }
            else{
                scanf("%d %lld %d", &parents[i], &a[i], &v[i]);
                child_cnt[parents[i]]++;
                children[parents[i]][child_cnt[parents[i]]]=i;
            }
        }
        // Compute depth using BFS
        memset(depth_node, 0, sizeof(depth_node));
        depth_node[1]=1;
        max_depth=1;
        int queue[MAX_N];
        int front=0, rear=0;
        queue[rear++]=1;
        while(front < rear){
            int u = queue[front++];
            for(int i=1;i<=child_cnt[u];i++){
                int child = children[u][i];
                depth_node[child] = depth_node[u]+1;
                if(depth_node[child] > max_depth){
                    max_depth = depth_node[child];
                }
                queue[rear++]=child;
            }
        }
        // Initialize DP
        memset(dp, -1, sizeof(ll)* (k + max_depth +2));
        dp[0]=0;
        // DFS to perform tree DP
        // Implemented iteratively using a stack
        typedef struct{
            int node;
            int child_idx;
            ll local_a;
            int local_v;
        } StackNode;
        StackNode stack_nodes[MAX_N];
        int stack_top =0;
        stack_nodes[stack_top].node=1;
        stack_nodes[stack_top].child_idx=0;
        stack_nodes[stack_top].local_a=a[1];
        stack_nodes[stack_top].local_v=v[1];
        stack_top++;
        while(stack_top >0){
            StackNode current = stack_nodes[stack_top-1];
            if(current.child_idx < child_cnt[current.node]){
                // Push child to stack
                stack_nodes[stack_top].node = children[current.node][current.child_idx+1];
                stack_nodes[stack_top].child_idx=0;
                stack_nodes[stack_top].local_a=a[children[current.node][current.child_idx+1]];
                stack_nodes[stack_top].local_v=v[children[current.node][current.child_idx+1]];
                stack_top++;
                stack_nodes[stack_top-2].child_idx++;
                continue;
            }
            // Process current node
            // Take as many as possible from current node
            ll take_limit = a[current.node] < (k + max_depth) ? a[current.node] : (k + max_depth);
            for(int t=k + max_depth; t>=0; t--){
                if(dp[t] != -1){
                    for(ll cnt=1; cnt<=take_limit && t + cnt <=k + max_depth; cnt++){
                        if(dp[t + cnt] < dp[t] + cnt * (ll)v[current.node]){
                            dp[t + cnt] = dp[t] + cnt * (ll)v[current.node];
                        }
                    }
                }
            }
            stack_top--;
        }
        // Find the maximum happiness
        ll result =0;
        for(int t=0; t<=k + max_depth; t++){
            // Find h such that h >= max_depth_selected and h >= t -k
            // Since max_depth_selected <= max_depth, and h >= t -k
            // So h >= max(t -k, 1) and h >= max_depth_selected
            // To simplify, ensure t -k <= max_depth
            if(t - k <= max_depth && t - k >=1){
                if(dp[t] > result){
                    result = dp[t];
                }
            }
            else if(t -k <= max_depth && t -k <1){
                if(dp[t] > result){
                    result = dp[t];
                }
            }
        }
        printf("%lld\n", result);
    }
    return 0;
}
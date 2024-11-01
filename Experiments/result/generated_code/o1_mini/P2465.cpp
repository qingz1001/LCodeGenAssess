#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 101
#define MAXP 12
#define MAXMASK (1<<MAXP)
#define MAXT 4096

typedef struct Node {
    int children[MAXN];
    int child_cnt;
} Node;

typedef struct Rule {
    long long v;
    int mask;
} Rule;

Node tree[MAXN];
long long a_cost[MAXN][MAXP];
int p;
int n;
int t;
Rule rules[MAXT];
long long profit_val[MAXMASK];
long long cost_sum[MAXN][MAXMASK];
long long memo_cache[MAXN][MAXMASK];
int computed_dp[MAXN][MAXMASK];
int department_bits[MAXP];

long long dp(int node, int mask);

long long max_ll(long long a, long long b){
    return a > b ? a : b;
}

int main(){
    int i, j, x, y;
    // Read n and p
    scanf("%d %d", &n, &p);
    // Read n-1 edges
    for(i=0;i<n-1;i++){
        scanf("%d %d", &x, &y);
        tree[x].children[tree[x].child_cnt++] = y;
        tree[y].children[tree[y].child_cnt++] = x;
    }
    // Read a[i][j]
    for(i=1;i<=n;i++){
        for(j=0;j<p;j++){
            scanf("%lld", &a_cost[i][j]);
        }
    }
    // Read t
    scanf("%d", &t);
    // Read t rules
    for(i=0;i<t;i++){
        int v, c, dep;
        scanf("%d %d", &v, &c);
        int mask =0;
        for(j=0;j<c;j++){
            scanf("%d", &dep);
            mask |= (1<<(dep-1));
        }
        rules[i].v = v;
        rules[i].mask = mask;
    }
    // Precompute profit_val
    for(i=0;i<(1<<p);i++){
        long long total =0;
        for(j=0;j<t;j++){
            if( (rules[j].mask & ~i) ==0 ){
                total += rules[j].v;
            }
        }
        profit_val[i] = total;
    }
    // Precompute cost_sum
    for(i=1;i<=n;i++){
        cost_sum[i][0] =0;
        for(j=1;j<(1<<p);j++){
            int last = j & -j;
            int bit = 0;
            while(((1<<bit) & last) ==0) bit++;
            cost_sum[i][j] = cost_sum[i][j ^ last] + a_cost[i][bit];
        }
    }
    // Build the tree as rooted tree from node 1
    // Remove the parent from children lists
    // Use BFS to assign children correctly
    int parent[MAXN];
    memset(parent, 0, sizeof(parent));
    int queue[MAXN];
    int front=0, rear=0;
    queue[rear++] =1;
    while(front < rear){
        int current = queue[front++];
        int new_children[MAXN];
        int new_cnt=0;
        for(i=0;i<tree[current].child_cnt;i++){
            int child = tree[current].children[i];
            if(child != parent[current]){
                parent[child] = current;
                tree[current].children[new_cnt++] = child;
                queue[rear++] = child;
            }
        }
        tree[current].child_cnt = new_cnt;
    }
    // Initialize memo_cache
    for(i=1;i<=n;i++){
        for(j=0;j<(1<<p);j++){
            memo_cache[i][j] = LLONG_MIN;
            computed_dp[i][j] = 0;
        }
    }
    // Compute DP starting from root node 1 with mask 0
    long long result = dp(1, 0);
    printf("%lld\n", result);
    return 0;
}

long long dp(int node, int mask){
    if(computed_dp[node][mask]){
        return memo_cache[node][mask];
    }
    computed_dp[node][mask] =1;
    long long max_profit = LLONG_MIN;
    // Iterate over all subsets x of ~mask
    for(int x=0; x<(1<<p); x++){
        if( (x & mask) !=0 ) continue;
        int new_mask = mask | x;
        long long current_profit = profit_val[new_mask] - cost_sum[node][x];
        // Add profits from children
        for(int i=0;i<tree[node].child_cnt;i++){
            int child = tree[node].children[i];
            current_profit += dp(child, new_mask);
        }
        if(current_profit > max_profit){
            max_profit = current_profit;
        }
    }
    memo_cache[node][mask] = max_profit;
    return memo_cache[node][mask];
}
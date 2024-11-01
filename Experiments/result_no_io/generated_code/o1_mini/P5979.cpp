#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001
#define LOG_MAX 20
#define MOD 1000000007

typedef long long ll;

// Sparse Tables for range maximum of c and range minimum of d
int log_table[MAX_N];
int st_max_c[LOG_MAX][MAX_N];
int st_min_d[LOG_MAX][MAX_N];

// DP arrays
int dp_max_arr[MAX_N];
ll cnt_dp[MAX_N];

// Segment Tree
typedef struct {
    int max_dp;
    ll sum_cnt;
} Node;

Node tree_nodes[4 * MAX_N];

// Function to compute maximum
int max_val(int a, int b){
    return a > b ? a : b;
}

// Function to compute minimum
int min_val(int a, int b){
    return a < b ? a : b;
}

// Build Sparse Tables
void build_sparse_tables(int n, int c[], int d[]){
    for(int i=1;i<=n;i++){
        st_max_c[0][i] = c[i];
        st_min_d[0][i] = d[i];
    }
    for(int k=1; k<LOG_MAX; k++){
        for(int i=1; i + (1<<k) -1 <=n; i++){
            st_max_c[k][i] = max_val(st_max_c[k-1][i], st_max_c[k-1][i + (1<<(k-1))]);
            st_min_d[k][i] = min_val(st_min_d[k-1][i], st_min_d[k-1][i + (1<<(k-1))]);
        }
    }
}

// Query maximum of c in range [l, r]
int query_max_c(int l, int r){
    int j = log_table[r - l +1];
    return max_val(st_max_c[j][l], st_max_c[j][r - (1<<j) +1]);
}

// Query minimum of d in range [l, r]
int query_min_d(int l, int r){
    int j = log_table[r - l +1];
    return min_val(st_min_d[j][l], st_min_d[j][r - (1<<j) +1]);
}

// Build log table
void build_log_table(int n){
    log_table[1] =0;
    for(int i=2;i<=n;i++) {
        log_table[i] = log_table[i/2] +1;
    }
}

// Update Segment Tree at position pos
void update_tree_func(int node, int l, int r, int pos, int dp_val, ll cnt_val){
    if(l == r){
        tree_nodes[node].max_dp = dp_val;
        tree_nodes[node].sum_cnt = cnt_val;
        return;
    }
    int mid = (l + r)/2;
    if(pos <= mid){
        update_tree_func(2*node, l, mid, pos, dp_val, cnt_val);
    }
    else{
        update_tree_func(2*node+1, mid+1, r, pos, dp_val, cnt_val);
    }
    if(tree_nodes[2*node].max_dp > tree_nodes[2*node+1].max_dp){
        tree_nodes[node].max_dp = tree_nodes[2*node].max_dp;
        tree_nodes[node].sum_cnt = tree_nodes[2*node].sum_cnt;
    }
    else if(tree_nodes[2*node].max_dp < tree_nodes[2*node+1].max_dp){
        tree_nodes[node].max_dp = tree_nodes[2*node+1].max_dp;
        tree_nodes[node].sum_cnt = tree_nodes[2*node+1].sum_cnt;
    }
    else{
        tree_nodes[node].max_dp = tree_nodes[2*node].max_dp;
        tree_nodes[node].sum_cnt = (tree_nodes[2*node].sum_cnt + tree_nodes[2*node+1].sum_cnt) % MOD;
    }
}

// Query Segment Tree in range [ql, qr]
typedef struct {
    int max_dp;
    ll sum_cnt;
} QueryResult;

QueryResult query_tree_func(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        QueryResult res;
        res.max_dp = -1;
        res.sum_cnt = 0;
        return res;
    }
    if(ql <= l && r <= qr){
        QueryResult res;
        res.max_dp = tree_nodes[node].max_dp;
        res.sum_cnt = tree_nodes[node].sum_cnt;
        return res;
    }
    int mid = (l + r)/2;
    QueryResult left = query_tree_func(2*node, l, mid, ql, qr);
    QueryResult right = query_tree_func(2*node+1, mid+1, r, ql, qr);
    QueryResult res;
    if(left.max_dp > right.max_dp){
        res.max_dp = left.max_dp;
        res.sum_cnt = left.sum_cnt;
    }
    else if(left.max_dp < right.max_dp){
        res.max_dp = right.max_dp;
        res.sum_cnt = right.sum_cnt;
    }
    else{
        res.max_dp = left.max_dp;
        res.sum_cnt = (left.sum_cnt + right.sum_cnt) % MOD;
    }
    return res;
}

// Check if a group of size k ending at i is valid
int is_valid(int k, int i, int c[], int d[]){
    int j = i - k +1;
    if(j <1) return 0;
    int max_c_val = query_max_c(j, i);
    int min_d_val = query_min_d(j, i);
    if(max_c_val <=k && min_d_val >=k) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    int *c = (int*)malloc((n+1)*sizeof(int));
    int *d = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d %d", &c[i], &d[i]);
    
    build_log_table(n);
    build_sparse_tables(n, c, d);
    
    // Initialize DP
    memset(dp_max_arr, -1, sizeof(dp_max_arr));
    memset(cnt_dp, 0, sizeof(cnt_dp));
    dp_max_arr[0] =0;
    cnt_dp[0] =1;
    
    // Initialize Segment Tree
    update_tree_func(1, 0, n, 0, dp_max_arr[0], cnt_dp[0]);
    
    for(int i=1;i<=n;i++){
        // Binary search for k_start
        int left =1, right =i;
        int k_start = i+1;
        while(left <= right){
            int mid = left + (right -left)/2;
            if(is_valid(mid, i, c, d)){
                k_start = mid;
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }
        // Binary search for k_end
        left =1; right =i;
        int k_fin =0;
        while(left <= right){
            int mid = left + (right -left)/2;
            if(is_valid(mid, i, c, d)){
                k_fin = mid;
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        if(k_start > k_fin){
            // No valid group ending at i
            dp_max_arr[i] = -1;
            cnt_dp[i] =0;
        }
        else{
            int j_left = i - k_fin;
            int j_right = i - k_start;
            if(j_right <0) j_right =0;
            if(j_left <0) j_left =0;
            QueryResult res = query_tree_func(1, 0, n, j_left, j_right);
            if(res.max_dp == -1){
                dp_max_arr[i] = -1;
                cnt_dp[i] =0;
            }
            else{
                dp_max_arr[i] = res.max_dp +1;
                cnt_dp[i] = res.sum_cnt % MOD;
            }
        }
        if(dp_max_arr[i] != -1){
            update_tree_func(1, 0, n, i, dp_max_arr[i], cnt_dp[i]);
        }
    }
    
    if(dp_max_arr[n] == -1){
        printf("NIE\n");
    }
    else{
        printf("%d %lld\n", dp_max_arr[n], cnt_dp[n]);
    }
    
    free(c);
    free(d);
    return 0;
}
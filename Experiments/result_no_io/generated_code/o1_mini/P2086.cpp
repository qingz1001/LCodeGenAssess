#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Maximum N*M <= 500000
#define MAXNM 500000
#define MAXN 500005
#define MAXM 1005
#define MAXTREE (4*1000000)

// GCD function
ll gcd_func(ll a, ll b){
    if(b == 0) return a;
    return gcd_func(b, a % b);
}

ll *st_tree;
ll *st_lazy;
ll *grid;

// M is up to 1000
int N, M, X, Y, T;

// Build segment tree for a row
void build_row(int r, int node, int l, int r_end){
    int idx = r * 4 * M + node;
    if(l == r_end){
        st_tree[idx] = grid[r*M + l-1];
        return;
    }
    int mid = (l + r_end) / 2;
    build_row(r, 2*node, l, mid);
    build_row(r, 2*node+1, mid+1, r_end);
    if(st_tree[r * 4 * M + 2*node] == 0){
        st_tree[idx] = st_tree[r * 4 * M + 2*node+1];
    }
    else{
        st_tree[idx] = gcd_func(st_tree[r * 4 * M + 2*node], st_tree[r * 4 * M + 2*node+1]);
    }
}

// Push down for a row
void push_row(int r, int node, int l, int r_end){
    int idx = r * 4 * M + node;
    if(st_lazy[idx] != 0){
        // Update children
        int left = 2*node;
        int right = 2*node+1;
        int left_idx = r * 4 * M + left;
        int right_idx = r * 4 * M + right;
        st_tree[left_idx] += st_lazy[idx];
        st_tree[right_idx] += st_lazy[idx];
        st_lazy[left_idx] += st_lazy[idx];
        st_lazy[right_idx] += st_lazy[idx];
        st_lazy[idx] = 0;
    }
}

// Update range add for a row
void update_row(int r, int node, int l, int r_end, int ul, int ur, ll val){
    int idx = r * 4 * M + node;
    if(ur < l || ul > r_end) return;
    if(ul <= l && r_end <= ur){
        st_tree[idx] += val;
        st_lazy[idx] += val;
        return;
    }
    push_row(r, node, l, r_end);
    int mid = (l + r_end) / 2;
    update_row(r, 2*node, l, mid, ul, ur, val);
    update_row(r, 2*node+1, mid+1, r_end, ul, ur, val);
    st_tree[idx] = gcd_func(st_tree[r * 4 * M + 2*node], st_tree[r * 4 * M + 2*node+1]);
}

// Query range gcd for a row
ll query_row(int r, int node, int l, int r_end, int ql, int qr){
    int idx = r * 4 * M + node;
    if(qr < l || ql > r_end) return 0;
    if(ql <= l && r_end <= qr){
        return st_tree[idx];
    }
    push_row(r, node, l, r_end);
    int mid = (l + r_end) / 2;
    ll left = query_row(r, 2*node, l, mid, ql, qr);
    ll right = query_row(r, 2*node+1, mid+1, r_end, ql, qr);
    if(left == 0) return right;
    if(right == 0) return left;
    return gcd_func(left, right);
}

int main(){
    // Read N, M
    scanf("%d %d", &N, &M);
    // Read X, Y
    scanf("%d %d", &X, &Y);
    // Read T
    scanf("%d", &T);
    // Allocate grid
    grid = (ll*)malloc(N * M * sizeof(ll));
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%lld", &grid[i*M + j]);
        }
    }
    // Allocate segment trees
    st_tree = (ll*)calloc((4*N*M)+4, sizeof(ll));
    st_lazy = (ll*)calloc((4*N*M)+4, sizeof(ll));
    // Build all rows
    for(int r=0; r<N; r++){
        build_row(r, 1, 1, M);
    }
    // Process T operations
    for(int t=0; t<T; t++){
        int type;
        scanf("%d", &type);
        if(type == 0){
            // Query operation
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            // Calculate absolute row and column ranges
            int row_start = X - x1;
            int row_end = X + x2;
            int col_start = Y - y1;
            int col_end = Y + y2;
            if(row_start < 1) row_start = 1;
            if(row_end > N) row_end = N;
            if(col_start < 1) col_start = 1;
            if(col_end > M) col_end = M;
            ll res = 0;
            for(int r=row_start-1; r<row_end; r++){
                ll tmp = query_row(r, 1, 1, M, col_start, col_end);
                if(tmp == 0) continue;
                res = gcd_func(res, tmp);
                if(res == 1) break;
            }
            printf("%lld\n", res);
        }
        else{
            // Update operation
            int x1, y1, x2, y2;
            ll c;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &c);
            // Rows are from x1 to x2, columns from y1 to y2
            int row_start = x1;
            int row_end = x2;
            int col_start = y1;
            int col_end = y2;
            for(int r=row_start-1; r<row_end; r++){
                update_row(r, 1, 1, M, col_start, col_end, c);
            }
        }
    }
    // Free memory
    free(grid);
    free(st_tree);
    free(st_lazy);
    return 0;
}
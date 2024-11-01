#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 1000000000
#define MAXN 100005
#define ROWS 6

typedef struct {
    int mat[ROWS][ROWS];
} Matrix;

int n, Q;
int grid[ROWS][MAXN];
Matrix seg[4 * MAXN];

// Function to compute the matrix for a single column
Matrix compute_column(int col) {
    Matrix M;
    // Initialize adjacency within the column
    // The minimum path from i to j is the sum from min(i,j) to max(i,j)
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<ROWS;j++) {
            if(i <= j){
                int sum = 0;
                for(int k=i; k<=j; k++) sum += grid[k][col];
                M.mat[i][j] = sum;
            }
            else{
                int sum = 0;
                for(int k=j; k<=i; k++) sum += grid[k][col];
                M.mat[i][j] = sum;
            }
        }
    }
    return M;
}

// Function to combine two matrices with min-plus multiplication
Matrix combine(Matrix A, Matrix B){
    Matrix C;
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<ROWS;j++) {
            C.mat[i][j] = INF;
            for(int k=0;k<ROWS;k++) {
                if(A.mat[i][k] == INF || B.mat[k][j] == INF) continue;
                if(A.mat[i][k] + B.mat[k][j] < C.mat[i][j]){
                    C.mat[i][j] = A.mat[i][k] + B.mat[k][j];
                }
            }
        }
    }
    return C;
}

// Build the segment tree
void build(int node, int l, int r){
    if(l == r){
        seg[node] = compute_column(l);
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    seg[node] = combine(seg[2*node], seg[2*node+1]);
}

// Update the segment tree
void update_tree(int node, int l, int r, int pos){
    if(l == r){
        seg[node] = compute_column(l);
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) update_tree(2*node, l, mid, pos);
    else update_tree(2*node+1, mid+1, r, pos);
    seg[node] = combine(seg[2*node], seg[2*node+1]);
}

// Query the segment tree
Matrix query_tree(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        Matrix M;
        for(int i=0;i<ROWS;i++) {
            for(int j=0;j<ROWS;j++) {
                M.mat[i][j] = (i == j) ? 0 : INF;
            }
        }
        return M;
    }
    if(ql <= l && r <= qr){
        return seg[node];
    }
    int mid = (l + r) / 2;
    Matrix left = query_tree(2*node, l, mid, ql, qr);
    Matrix right = query_tree(2*node+1, mid+1, r, ql, qr);
    return combine(left, right);
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<ROWS;i++) {
        for(int j=0; j<n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    build(1, 0, n-1);
    scanf("%d", &Q);
    while(Q--){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            x--; y--;
            grid[x][y] = c;
            update_tree(1, 0, n-1, y);
        }
        else if(type == 2){
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--; y1--; x2--; y2--;
            if(y1 > y2){
                int tmp = y1; y1 = y2; y2 = tmp;
                tmp = x1; x1 = x2; x2 = tmp;
            }
            Matrix res = query_tree(1, 0, n-1, y1, y2);
            if(res.mat[x1][x2] >= INF) printf("-1\n");
            else printf("%d\n", res.mat[x1][x2]);
        }
    }
    return 0;
}
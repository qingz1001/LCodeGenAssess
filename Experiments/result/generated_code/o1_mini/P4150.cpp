#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define INF 100000000000000LL

typedef struct {
    long long m[6][6];
} Matrix;

Matrix tree_st[4 * MAXN];
long long d[6][MAXN];
int n;

// Function to perform min-plus matrix multiplication
Matrix multiply(Matrix a, Matrix b){
    Matrix res;
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            res.m[i][j] = INF;
            for(int k=0;k<6;k++){
                if(a.m[i][k] + b.m[k][j] < res.m[i][j]){
                    res.m[i][j] = a.m[i][k] + b.m[k][j];
                }
            }
        }
    }
    return res;
}

// Build the segment tree
void build_tree(int node, int l, int r){
    if(l == r){
        // Calculate prefix sums for column l
        long long prefix[6];
        prefix[0] = d[0][l];
        for(int i=1;i<6;i++) prefix[i] = prefix[i-1] + d[i][l];
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(i <= j){
                    tree_st[node].m[i][j] = prefix[j] - (i > 0 ? prefix[i-1] : 0);
                }
                else{
                    tree_st[node].m[i][j] = prefix[i] - (j > 0 ? prefix[j-1] : 0);
                }
            }
        }
    }
    else{
        int mid = (l + r) / 2;
        build_tree(2*node, l, mid);
        build_tree(2*node+1, mid+1, r);
        tree_st[node] = multiply(tree_st[2*node], tree_st[2*node+1]);
    }
}

// Update the segment tree
void update_tree(int node, int l, int r, int y){
    if(l == r){
        // Recalculate prefix sums for column y
        long long prefix[6];
        prefix[0] = d[0][y];
        for(int i=1;i<6;i++) prefix[i] = prefix[i-1] + d[i][y];
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                if(i <= j){
                    tree_st[node].m[i][j] = prefix[j] - (i > 0 ? prefix[i-1] : 0);
                }
                else{
                    tree_st[node].m[i][j] = prefix[i] - (j > 0 ? prefix[j-1] : 0);
                }
            }
        }
    }
    else{
        int mid = (l + r) / 2;
        if(y <= mid) update_tree(2*node, l, mid, y);
        else update_tree(2*node+1, mid+1, r, y);
        tree_st[node] = multiply(tree_st[2*node], tree_st[2*node+1]);
    }
}

// Query the segment tree
Matrix query_tree(int node, int l, int r, int ql, int qr){
    Matrix res;
    // Initialize res as INF matrix
    for(int i=0;i<6;i++) {
        for(int j=0;j<6;j++) {
            res.m[i][j] = (i == j) ? 0 : INF;
        }
    }
    if(ql > r || qr < l){
        return res;
    }
    if(ql <= l && r <= qr){
        return tree_st[node];
    }
    int mid = (l + r) / 2;
    Matrix left = query_tree(2*node, l, mid, ql, qr);
    Matrix right = query_tree(2*node+1, mid+1, r, ql, qr);
    // Combine left and right
    Matrix combined;
    for(int i=0;i<6;i++) {
        for(int j=0;j<6;j++) {
            combined.m[i][j] = INF;
            for(int k=0;k<6;k++){
                if(left.m[i][k] + right.m[k][j] < combined.m[i][j]){
                    combined.m[i][j] = left.m[i][k] + right.m[k][j];
                }
            }
        }
    }
    return combined;
}

int main(){
    int Q;
    // Read n
    scanf("%d", &n);
    // Read 6 rows of n columns
    for(int i=0;i<6;i++){
        for(int j=1;j<=n;j++){
            scanf("%lld", &d[i][j]);
        }
    }
    // Build the segment tree
    build_tree(1, 1, n);
    // Read Q
    scanf("%d", &Q);
    while(Q--){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y;
            long long c;
            scanf("%d %d %lld", &x, &y, &c);
            x--; // 0-based
            d[x][y] = c;
            update_tree(1, 1, n, y);
        }
        else if(type == 2){
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--; x2--; // 0-based
            if(y1 <= y2){
                Matrix res = query_tree(1, 1, n, y1, y2);
                printf("%lld\n", res.m[x1][x2]);
            }
            else{
                Matrix res = query_tree(1, 1, n, y2, y1);
                printf("%lld\n", res.m[x2][x1]);
            }
        }
    }
    return 0;
}
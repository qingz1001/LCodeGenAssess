#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAXN 500005
#define MAXM 100005
#define MAXTREE 2000000

ll treeArr[2000000];
ll lazyArrGlobal[2000000];
ll initialValues[500005];
int N, M, X, Y, T;

// Function to compute GCD
ll gcd_func(ll a, ll b){
    while(b != 0){
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Build segment tree for a specific row
void build(int row, int node, int l, int r, ll *initial){
    int idx = row * 4 * M + node;
    if(l == r){
        treeArr[idx] = initial[l-1];
        return;
    }
    int mid = (l + r) / 2;
    build(row, node*2, l, mid, initial);
    build(row, node*2+1, mid+1, r, initial);
    treeArr[idx] = gcd_func(treeArr[row * 4 * M + node*2], treeArr[row * 4 * M + node*2+1]);
}

// Push down the lazy value
void push_down(int row, int node, int l, int r){
    int idx = row * 4 * M + node;
    if(lazyArrGlobal[idx] != 0){
        ll val = lazyArrGlobal[idx];
        int left = node * 2;
        int right = node * 2 +1;
        int mid = (l + r) /2;
        int idx_left = row *4 * M + left;
        int idx_right = row *4 * M + right;
        
        treeArr[idx_left] += val;
        treeArr[idx_right] += val;
        lazyArrGlobal[idx_left] += val;
        lazyArrGlobal[idx_right] += val;
        lazyArrGlobal[idx] = 0;
    }
}

// Update segment tree for a specific row
void update_range(int row, int node, int l, int r, int ul, int ur, ll val){
    int idx = row *4 * M + node;
    if(ul > r || ur < l){
        return;
    }
    if(ul <= l && r <= ur){
        treeArr[idx] += val;
        lazyArrGlobal[idx] += val;
        return;
    }
    push_down(row, node, l, r);
    int mid = (l + r)/2;
    update_range(row, node*2, l, mid, ul, ur, val);
    update_range(row, node*2+1, mid+1, r, ul, ur, val);
    treeArr[idx] = gcd_func(treeArr[row *4*M + node*2], treeArr[row *4*M + node*2+1]);
}

// Query segment tree for a specific row
ll query_range(int row, int node, int l, int r, int ql, int qr){
    int idx = row *4 * M + node;
    if(ql > r || qr < l){
        return 0;
    }
    if(ql <= l && r <= qr){
        return treeArr[idx];
    }
    push_down(row, node, l, r);
    int mid = (l + r)/2;
    ll left = query_range(row, node*2, l, mid, ql, qr);
    ll right = query_range(row, node*2+1, mid+1, r, ql, qr);
    if(left == 0) return right;
    if(right == 0) return left;
    return gcd_func(left, right);
}

int main(){
    // Fast IO
    scanf("%d %d", &N, &M);
    scanf("%d %d", &X, &Y);
    scanf("%d", &T);
    // Read initial grid
    for(int i=0;i<N*M;i++){
        scanf("%lld", &initialValues[i]);
    }
    // Build all segment trees
    for(int row=0; row<N; row++){
        build(row, 1, 1, M, &initialValues[row*M]);
    }
    // Process operations
    for(int op=0; op<T; op++){
        int type;
        scanf("%d", &type);
        if(type == 0){
            int up, left, down, right;
            scanf("%d %d %d %d", &up, &left, &down, &right);
            int r1 = X - up;
            if(r1 < 1) r1 = 1;
            int r2 = X + down;
            if(r2 > N) r2 = N;
            int c1 = Y - left;
            if(c1 < 1) c1 = 1;
            int c2 = Y + right;
            if(c2 > M) c2 = M;
            if(r1 > r2 || c1 > c2){
                printf("0\n");
                continue;
            }
            ll total_gcd = 0;
            for(int row=r1-1; row<r2; row++){
                ll row_gcd = query_range(row, 1, 1, M, c1, c2);
                if(row_gcd ==0){
                    continue;
                }
                if(total_gcd ==0){
                    total_gcd = row_gcd;
                }
                else{
                    total_gcd = gcd_func(total_gcd, row_gcd);
                }
                if(total_gcd ==1){
                    break;
                }
            }
            printf("%lld\n", total_gcd);
        }
        else{
            int x1, y1, x2, y2;
            ll c;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &c);
            if(x1 > x2) {int tmp=x1; x1=x2; x2=tmp;}
            if(y1 > y2) {int tmp=y1; y1=y2; y2=tmp;}
            for(int row=x1-1; row<x2; row++){
                update_range(row, 1, 1, M, y1, y2, c);
            }
        }
    }
    return 0;
}
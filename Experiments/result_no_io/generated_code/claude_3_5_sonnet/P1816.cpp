#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 100000
#define MAX_N 100000

int accounts[MAX_M];
int st[MAX_M][20];

int log2_floor(int x) {
    return 31 - __builtin_clz(x);
}

void build_sparse_table(int m) {
    for (int i = 0; i < m; i++) {
        st[i][0] = accounts[i];
    }
    
    for (int j = 1; (1 << j) <= m; j++) {
        for (int i = 0; i + (1 << j) <= m; i++) {
            st[i][j] = (st[i][j-1] < st[i + (1 << (j-1))][j-1]) ? 
                        st[i][j-1] : st[i + (1 << (j-1))][j-1];
        }
    }
}

int query(int l, int r) {
    int j = log2_floor(r - l + 1);
    return (st[l][j] < st[r - (1 << j) + 1][j]) ? 
            st[l][j] : st[r - (1 << j) + 1][j];
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &accounts[i]);
    }
    
    build_sparse_table(m);
    
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d ", query(a-1, b-1));
    }
    
    return 0;
}
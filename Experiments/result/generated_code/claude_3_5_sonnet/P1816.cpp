#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 100000
#define MAX_N 100000

int m, n;
int accounts[MAX_M + 1];
int st[MAX_M + 1][20];

void build_st() {
    for (int i = 1; i <= m; i++) {
        st[i][0] = accounts[i];
    }
    
    for (int j = 1; (1 << j) <= m; j++) {
        for (int i = 1; i + (1 << j) - 1 <= m; i++) {
            st[i][j] = (st[i][j-1] < st[i + (1 << (j-1))][j-1]) ? 
                        st[i][j-1] : st[i + (1 << (j-1))][j-1];
        }
    }
}

int query(int l, int r) {
    int k = 0;
    while ((1 << (k+1)) <= r - l + 1) k++;
    return (st[l][k] < st[r - (1 << k) + 1][k]) ? 
            st[l][k] : st[r - (1 << k) + 1][k];
}

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 1; i <= m; i++) {
        scanf("%d", &accounts[i]);
    }
    
    build_st();
    
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d ", query(a, b));
    }
    
    return 0;
}
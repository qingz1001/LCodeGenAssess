#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int size;
    ll *tree;
} FenwickTree;

// Initialize Fenwick Tree
FenwickTree* initFenwick(int size){
    FenwickTree *ft = (FenwickTree*)malloc(sizeof(FenwickTree));
    ft->size = size;
    ft->tree = (ll*)calloc(size + 1, sizeof(ll));
    return ft;
}

// Update Fenwick Tree at index with value
void updateFenwick(FenwickTree *ft, int index, ll value){
    while(index <= ft->size){
        ft->tree[index] += value;
        index += index & (-index);
    }
}

// Query prefix sum up to index
ll queryFenwick(FenwickTree *ft, int index){
    ll res = 0;
    while(index > 0){
        res += ft->tree[index];
        index -= index & (-index);
    }
    return res;
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    
    // Initialize Fenwick Trees
    FenwickTree *rows = initFenwick(n);
    FenwickTree *cols = initFenwick(m);
    
    // Initialize parity arrays
    char *Rx_parity = (char*)calloc(n + 1, sizeof(char));
    char *Cy_parity = (char*)calloc(m + 1, sizeof(char));
    
    for(int i = 0; i < q; i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y;
            scanf("%d %d", &x, &y);
            // Toggle row x
            if(Rx_parity[x] == 0){
                Rx_parity[x] = 1;
                updateFenwick(rows, x, 1);
            }
            else{
                Rx_parity[x] = 0;
                updateFenwick(rows, x, -1);
            }
            // Toggle column y
            if(Cy_parity[y] == 0){
                Cy_parity[y] = 1;
                updateFenwick(cols, y, 1);
            }
            else{
                Cy_parity[y] = 0;
                updateFenwick(cols, y, -1);
            }
        }
        else if(type == 2){
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            // Count odd rows in [x1, x2]
            ll Ox = queryFenwick(rows, x2) - queryFenwick(rows, x1 -1);
            ll Ex = (ll)(x2 - x1 +1) - Ox;
            // Count odd columns in [y1, y2]
            ll Oy = queryFenwick(cols, y2) - queryFenwick(cols, y1 -1);
            ll Ey = (ll)(y2 - y1 +1) - Oy;
            // Calculate answer
            ll ans = Ox * Ey + Ex * Oy;
            printf("%lld\n", ans);
        }
    }
    
    // Free memory
    free(rows->tree);
    free(rows);
    free(cols->tree);
    free(cols);
    free(Rx_parity);
    free(Cy_parity);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAX 100005

ll bit_row[MAX];
ll bit_col[MAX];
int row_parity_arr[MAX];
int col_parity_arr[MAX];
int n, m, q;

// Function to update BIT
void bit_add(ll *bit, int size, int idx, int delta){
    while(idx <= size){
        bit[idx] += delta;
        idx += idx & (-idx);
    }
}

// Function to get prefix sum from BIT
ll bit_sum(ll *bit, int idx){
    ll res = 0;
    while(idx > 0){
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int main(){
    // Fast IO
    ios:
    if (fgetc(stdin) == EOF) goto end;
    
    // Read n, m, q
    scanf("%d %d %d", &n, &m, &q);
    
    // Initialize parities
    for(int i=1;i<=n;i++) row_parity_arr[i] = 0;
    for(int i=1;i<=m;i++) col_parity_arr[i] = 0;
    
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y;
            scanf("%d %d", &x, &y);
            // Toggle row parity
            if(row_parity_arr[x] == 0){
                row_parity_arr[x] = 1;
                bit_add(bit_row, n, x, 1);
            }
            else{
                row_parity_arr[x] = 0;
                bit_add(bit_row, n, x, -1);
            }
            // Toggle column parity
            if(col_parity_arr[y] == 0){
                col_parity_arr[y] = 1;
                bit_add(bit_col, m, y, 1);
            }
            else{
                col_parity_arr[y] = 0;
                bit_add(bit_col, m, y, -1);
            }
        }
        else if(type == 2){
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            ll A = bit_sum(bit_row, x2) - bit_sum(bit_row, x1-1);
            ll B = bit_sum(bit_col, y2) - bit_sum(bit_col, y1-1);
            int R = x2 - x1 + 1;
            int C = y2 - y1 + 1;
            ll ans = A * (C - B) + (R - A) * B;
            printf("%lld\n", ans);
        }
    }
    end:
    return 0;
}
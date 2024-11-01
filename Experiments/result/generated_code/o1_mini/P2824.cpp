#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001
#define MAXLOG 20

int cum[20][MAXN];
int temp_left_arr[100001];
int temp_right_arr[100001];
int pos_val[MAXN];
int operations_op[MAXN];
int operations_l[MAXN];
int operations_r[MAXN];

// Recursive function to build the Wavelet Tree
void buildWT(int *a, int n, int low, int high, int depth){
    if(low == high || depth >= MAXLOG){
        return;
    }
    int mid = (low + high) / 2;
    cum[depth][0] = 0;
    int k_left = 0, k_right = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] <= mid){
            cum[depth][i] = cum[depth][i-1] + 1;
            temp_left_arr[++k_left] = a[i];
        }
        else{
            cum[depth][i] = cum[depth][i-1];
            temp_right_arr[++k_right] = a[i];
        }
    }
    buildWT(temp_left_arr, k_left, low, mid, depth + 1);
    buildWT(temp_right_arr, k_right, mid + 1, high, depth + 1);
}

// Recursive function to find the k-th smallest element in range [l, r]
int kthWT(int l, int r, int k, int low, int high, int depth){
    if(low == high){
        return low;
    }
    int mid = (low + high) / 2;
    int cnt = cum[depth][r] - cum[depth][l-1];
    if(k <= cnt){
        int new_l = cum[depth][l-1] + 1;
        int new_r = cum[depth][r];
        return kthWT(new_l, new_r, k, low, mid, depth + 1);
    }
    else{
        int new_l = l - cum[depth][l-1];
        int new_r = r - cum[depth][r];
        return kthWT(new_l, new_r, k - cnt, mid + 1, high, depth + 1);
    }
}

int main(){
    int n, m;
    // Read n and m
    scanf("%d %d", &n, &m);
    int a_initial[MAXN];
    int a_wave[MAXN];
    // Read the initial array and store positions
    for(int i =1; i<=n; i++){
        scanf("%d", &a_initial[i]);
        a_wave[i] = a_initial[i];
        pos_val[a_initial[i]] = i;
    }
    // Build the Wavelet Tree
    buildWT(a_wave, n, 1, n, 0);
    // Read m operations
    for(int i=1; i<=m; i++){
        scanf("%d %d %d", &operations_op[i], &operations_l[i], &operations_r[i]);
    }
    // Read q
    int q;
    scanf("%d", &q);
    int q_current = q;
    // Process operations in reverse
    for(int i=m; i>=1; i--){
        int op = operations_op[i];
        int l = operations_l[i];
        int r = operations_r[i];
        if(q_current >= l && q_current <= r){
            int k;
            if(op == 0){
                k = q_current - l + 1;
            }
            else{
                k = r - q_current + 1;
            }
            int val = kthWT(l, r, k, 1, n, 0);
            q_current = pos_val[val];
        }
    }
    // Output the result
    printf("%d\n", a_initial[q_current]);
    return 0;
}
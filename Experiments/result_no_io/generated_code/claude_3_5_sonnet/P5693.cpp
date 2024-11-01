#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 400005
#define BLOCK_SIZE 700

typedef long long ll;

ll a[MAXN], sum[MAXN], add[MAXN];
int n, q, block_cnt;
ll max_sum[MAXN], prefix_max[MAXN], suffix_max[MAXN];

void build() {
    block_cnt = (n - 1) / BLOCK_SIZE + 1;
    for (int i = 0; i < block_cnt; i++) {
        int l = i * BLOCK_SIZE, r = (i + 1) * BLOCK_SIZE - 1;
        if (r >= n) r = n - 1;
        
        ll cur_sum = 0, max_prefix = 0, max_suffix = 0, max_subarray = 0;
        for (int j = l; j <= r; j++) {
            cur_sum += a[j];
            sum[j] = cur_sum;
            max_prefix = (max_prefix > cur_sum) ? max_prefix : cur_sum;
            max_subarray = (max_subarray > cur_sum - max_suffix) ? max_subarray : cur_sum - max_suffix;
            max_suffix = (max_suffix < cur_sum) ? max_suffix : cur_sum;
        }
        
        max_sum[i] = max_subarray;
        prefix_max[i] = max_prefix;
        suffix_max[i] = cur_sum - max_suffix;
    }
}

void update(int l, int r, ll x) {
    int bl = l / BLOCK_SIZE, br = r / BLOCK_SIZE;
    if (bl == br) {
        for (int i = l; i <= r; i++) a[i] += x;
        int block = bl;
        int block_l = block * BLOCK_SIZE, block_r = (block + 1) * BLOCK_SIZE - 1;
        if (block_r >= n) block_r = n - 1;
        
        ll cur_sum = 0, max_prefix = 0, max_suffix = 0, max_subarray = 0;
        for (int i = block_l; i <= block_r; i++) {
            cur_sum += a[i];
            sum[i] = cur_sum;
            max_prefix = (max_prefix > cur_sum) ? max_prefix : cur_sum;
            max_subarray = (max_subarray > cur_sum - max_suffix) ? max_subarray : cur_sum - max_suffix;
            max_suffix = (max_suffix < cur_sum) ? max_suffix : cur_sum;
        }
        
        max_sum[block] = max_subarray;
        prefix_max[block] = max_prefix;
        suffix_max[block] = cur_sum - max_suffix;
    } else {
        for (int i = l; i < (bl + 1) * BLOCK_SIZE; i++) a[i] += x;
        for (int i = bl + 1; i < br; i++) add[i] += x;
        for (int i = br * BLOCK_SIZE; i <= r; i++) a[i] += x;
        
        for (int block = bl; block <= br; block++) {
            int block_l = block * BLOCK_SIZE, block_r = (block + 1) * BLOCK_SIZE - 1;
            if (block_r >= n) block_r = n - 1;
            
            ll cur_sum = 0, max_prefix = 0, max_suffix = 0, max_subarray = 0;
            for (int i = block_l; i <= block_r; i++) {
                cur_sum += a[i];
                sum[i] = cur_sum;
                max_prefix = (max_prefix > cur_sum) ? max_prefix : cur_sum;
                max_subarray = (max_subarray > cur_sum - max_suffix) ? max_subarray : cur_sum - max_suffix;
                max_suffix = (max_suffix < cur_sum) ? max_suffix : cur_sum;
            }
            
            max_sum[block] = max_subarray;
            prefix_max[block] = max_prefix;
            suffix_max[block] = cur_sum - max_suffix;
        }
    }
}

ll query(int l, int r) {
    int bl = l / BLOCK_SIZE, br = r / BLOCK_SIZE;
    ll res = LLONG_MIN, sum_l = 0, sum_r = 0;
    
    if (bl == br) {
        for (int i = l; i <= r; i++) {
            sum_r += a[i];
            res = (res > sum_r - sum_l) ? res : sum_r - sum_l;
            sum_l = (sum_l < sum_r) ? sum_l : sum_r;
        }
        return res;
    }
    
    for (int i = l; i < (bl + 1) * BLOCK_SIZE; i++) {
        sum_r += a[i];
        res = (res > sum_r - sum_l) ? res : sum_r - sum_l;
        sum_l = (sum_l < sum_r) ? sum_l : sum_r;
    }
    
    ll total_sum = sum_r;
    for (int i = bl + 1; i < br; i++) {
        res = (res > max_sum[i] + add[i] * BLOCK_SIZE) ? res : max_sum[i] + add[i] * BLOCK_SIZE;
        ll cur_prefix = prefix_max[i] + total_sum + add[i] * BLOCK_SIZE;
        res = (res > cur_prefix) ? res : cur_prefix;
        total_sum += sum[(i + 1) * BLOCK_SIZE - 1] + add[i] * BLOCK_SIZE;
    }
    
    sum_l = (sum_l < total_sum) ? sum_l : total_sum;
    for (int i = br * BLOCK_SIZE; i <= r; i++) {
        sum_r += a[i];
        res = (res > sum_r - sum_l) ? res : sum_r - sum_l;
        sum_l = (sum_l < sum_r) ? sum_l : sum_r;
    }
    
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    
    build();
    
    while (q--) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        l--; r--;
        
        if (op == 1) {
            ll x;
            scanf("%lld", &x);
            update(l, r, x);
        } else {
            printf("%lld\n", query(l, r));
        }
    }
    
    return 0;
}
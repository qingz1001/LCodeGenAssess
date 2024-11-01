#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    ll T, n;
    scanf("%lld %lld", &T, &n);
    ll *left = (ll*)malloc(n * sizeof(ll));
    ll *right = (ll*)malloc(n * sizeof(ll));
    int l = 0, r = 0;
    for(int i = 0; i < n; i++){
        ll x;
        scanf("%lld", &x);
        if(x < 0){
            left[l++] = -x;
        }
        else{
            right[r++] = x;
        }
    }
    qsort(left, l, sizeof(ll), cmp);
    qsort(right, r, sizeof(ll), cmp);
    ll *prefix_left = (ll*)malloc((l+1) * sizeof(ll));
    ll *prefix_right = (ll*)malloc((r+1) * sizeof(ll));
    prefix_left[0] = 0;
    for(int i = 1; i <= l; i++) prefix_left[i] = prefix_left[i-1] + left[i-1];
    prefix_right[0] = 0;
    for(int i = 1; i <= r; i++) prefix_right[i] = prefix_right[i-1] + right[i-1];
    int max_vis = 0;
    for(int i = 0; i <= l; i++){
        if(prefix_left[i] > T) break;
        ll remain = T - prefix_left[i];
        // Option 1: go left then right
        // Distance: prefix_left[i] + right[j]
        // Alternative: going to right first then left
        // To ensure minimum distance, it's better to consider the max of two
        // So the total time can be min of:
        // 2 * prefix_left[i] + right[j]
        // or prefix_left[i] + 2 * right[j]
        // Here we consider going left first then right
        // So total time is prefix_left[i] + right[j]
        // But need to optimize the path
        // To simplify, assume total time is prefix_left[i] + prefix_right[j]
        // But to be accurate, we'll consider two options
        // Option A: go left first, then to right
        // Time = prefix_left[i] + right[j]
        // Option B: go right first, then to left
        // Time = prefix_right[j] + left[i]
        // So we need to find j such that max(prefix_left[i], prefix_right[j]) + min(prefix_left[i], prefix_right[j]) <= T
        // To simplify, find j such that prefix_left[i] + prefix_right[j] <= T
        // So binary search on j
        int low = 0, high = r, res = 0;
        while(low <= high){
            int mid = (low + high) / 2;
            if(prefix_right[mid] + prefix_left[i] <= T){
                res = mid;
                low = mid + 1;
            }
            else{
                high = mid -1;
            }
        }
        if(i + res > max_vis) max_vis = i + res;
    }
    for(int i = 0; i <= r; i++){
        if(prefix_right[i] > T) break;
        ll remain = T - prefix_right[i];
        int low = 0, high = l, res = 0;
        while(low <= high){
            int mid = (low + high) /2;
            if(prefix_left[mid] + prefix_right[i] <= T){
                res = mid;
                low = mid +1;
            }
            else{
                high = mid -1;
            }
        }
        if(i + res > max_vis) max_vis = i + res;
    }
    printf("%d\n", max_vis);
    free(left);
    free(right);
    free(prefix_left);
    free(prefix_right);
    return 0;
}
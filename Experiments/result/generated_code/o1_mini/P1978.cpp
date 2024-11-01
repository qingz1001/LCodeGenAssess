#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

int compare(const void *a, const void *b) {
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int binary_search_ll(ll *arr, int n, ll target){
    int left = 0, right = n-1;
    while(left <= right){
        int mid = left + (right - left)/2;
        if(arr[mid] == target) return mid;
        else if(arr[mid] < target) left = mid +1;
        else right = mid -1;
    }
    return -1;
}

int main(){
    int n;
    ll k;
    scanf("%d %lld", &n, &k);
    ll *a = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    qsort(a, n, sizeof(ll), compare);
    int *excluded = (int*)calloc(n, sizeof(int));
    int count =0;
    for(int i=0;i<n;i++){
        if(!excluded[i]){
            ll x = a[i];
            int overflow =0;
            __int128 y128 = ((__int128)x) * k;
            if(y128 > LLONG_MAX || y128 < LLONG_MIN){
                // Overflow, do nothing
            }
            else{
                ll y = (ll)y128;
                int j = binary_search_ll(a, n, y);
                if(j != -1){
                    excluded[j] =1;
                }
            }
            count++;
        }
    }
    printf("%d\n", count);
    free(a);
    free(excluded);
    return 0;
}
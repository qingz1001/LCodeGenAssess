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
    int N, C;
    scanf("%d %d", &N, &C);
    ll *arr = (ll*)malloc(N * sizeof(ll));
    for(int i=0;i<N;i++) scanf("%lld", &arr[i]);
    qsort(arr, N, sizeof(ll), cmp);
    ll left=0, right= arr[N-1] - arr[0], res=0;
    while(left <= right){
        ll mid = left + (right - left)/2;
        int count=1;
        ll last = arr[0];
        for(int i=1;i<N;i++){
            if(arr[i] - last >= mid){
                count++;
                last = arr[i];
                if(count >= C) break;
            }
        }
        if(count >= C){
            res = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    printf("%lld\n", res);
    free(arr);
    return 0;
}
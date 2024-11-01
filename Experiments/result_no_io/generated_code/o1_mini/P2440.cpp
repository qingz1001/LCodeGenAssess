#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    ll k;
    scanf("%d %lld", &n, &k);
    ll* L = (ll*)malloc(n * sizeof(ll));
    ll maxL = 0;
    for(int i=0;i<n;i++){
        scanf("%lld", &L[i]);
        if(L[i] > maxL) maxL = L[i];
    }
    ll left=1, right=maxL, res=0;
    while(left <= right){
        ll mid = left + (right - left)/2;
        ll total=0;
        for(int i=0;i<n;i++) total += L[i]/mid;
        if(total >= k){
            res = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    // Check if at least 1 can be cut
    ll total1=0;
    for(int i=0;i<n;i++) total1 += L[i];
    if(total1 < k){
        printf("0\n");
    }
    else{
        printf("%lld\n", res);
    }
    free(L);
    return 0;
}
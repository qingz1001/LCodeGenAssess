#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b) {
    ll x = *((ll*)b);
    ll y = *((ll*)a);
    if(x > y) return 1;
    else if(x < y) return -1;
    else return 0;
}

int main(){
    int n, k, L, R;
    scanf("%d %d %d %d", &n, &k, &L, &R);
    ll A[n+1];
    for(int i=1;i<=n;i++) scanf("%lld", &A[i]);
    ll prefix[n+1];
    prefix[0]=0;
    for(int i=1;i<=n;i++) prefix[i]=prefix[i-1]+A[i];
    int total = 0;
    for(int len=L; len<=R; len++) {
        if(len > n) break;
        total += (n - len +1);
    }
    ll *sums = (ll*)malloc(total * sizeof(ll));
    int idx=0;
    for(int len=L; len<=R; len++) {
        if(len > n) break;
        for(int i=len; i<=n; i++) {
            sums[idx++] = prefix[i] - prefix[i - len];
        }
    }
    qsort(sums, idx, sizeof(ll), cmp);
    ll res=0;
    for(int i=0;i<k;i++) res += sums[i];
    printf("%lld", res);
    free(sums);
}
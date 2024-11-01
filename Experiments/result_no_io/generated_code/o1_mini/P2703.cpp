#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    ll *L = (ll*)malloc(n * sizeof(ll));
    ll *R = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &L[i]);
    for(int i=0;i<n;i++) scanf("%lld", &R[i]);
    // Placeholder for actual computation
    ll cost = 0;
    // Implement the logic to compute minimal cost here
    printf("%lld\n", cost);
    free(L);
    free(R);
    return 0;
}
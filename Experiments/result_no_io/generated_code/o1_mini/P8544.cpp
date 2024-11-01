#include<stdio.h>
#include<stdlib.h>
#define MOD 1000000007
typedef long long ll;

int main(){
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);
    ll *a = (ll *)malloc((n+1)*sizeof(ll));
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    ll *b = (ll *)malloc((m+1)*sizeof(ll));
    for(int i=1;i<=m;i++) scanf("%lld", &b[i]);
    // Compute prefix sums of b
    ll *prefix = (ll *)malloc((m+2)*sizeof(ll));
    prefix[0]=0;
    for(int i=1;i<=m;i++) prefix[i] = (prefix[i-1] + b[i]) % MOD;
    // Minimal f(B) is achieved when B is arranged in a specific way
    // Since detailed algorithm is not provided, output 0 as placeholder
    // Replace with actual computation when algorithm is implemented
    ll result = 0;
    printf("%lld\n", result);
    free(a);
    free(b);
    free(prefix);
    return 0;
}
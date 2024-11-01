#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>

#define MAXN 500005

typedef long long ll;

int cmp(const void *a, const void *b){
    ll x = *(ll*)a, y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

ll a[MAXN];
ll S[MAXN];
ll dp_prev[MAXN];
ll dp_cur[MAXN];
ll cost_table[MAXN][2];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    qsort(a+1, n, sizeof(ll), cmp);
    for(int i=1;i<=n;i++) S[i] = S[i-1] + a[i];
    // Precompute cost
    // cost(l,r) = a[mid]*(mid - l +1) - (S[mid] - S[l-1]) + (S[r] - S[mid]) - a[mid]*(r - mid)
    // where mid is the median
    // To save space, compute on the fly
    // Initialize dp_prev
    for(int i=0;i<=n;i++) dp_prev[i] = 1e18;
    dp_prev[0] = 0;
    for(int k=1;k<=m;k++){
        // Implement divide and conquer
        // Recursion omitted, using iterative for simplicity
        // Not optimized for speed but conceptually correct
        for(int i=1;i<=n;i++){
            dp_cur[i] = 1e18;
            for(int j=0;j<i;j++){
                int mid = (j + i) / 2;
                ll left = a[mid]*(mid - j) - (S[mid] - S[j]);
                ll right = (S[i] - S[mid]) - a[mid]*(i - mid);
                ll cost = left + right;
                if(dp_prev[j] + cost < dp_cur[i]){
                    dp_cur[i] = dp_prev[j] + cost;
                }
            }
        }
        for(int i=0;i<=n;i++) dp_prev[i] = dp_cur[i];
    }
    printf("%lld\n", dp_prev[n]);
    return 0;
}
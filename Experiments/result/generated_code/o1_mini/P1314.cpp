#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define MAXN 200005
#define MAXW 1000001

typedef long long ll;

int main(){
    int n, m;
    ll s;
    scanf("%d %d %lld", &n, &m, &s);
    int *w = (int*)malloc((n+1) * sizeof(int));
    int *v = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d %d", &w[i], &v[i]);
    int *l = (int*)malloc((m+1) * sizeof(int));
    int *r = (int*)malloc((m+1) * sizeof(int));
    for(int i=1;i<=m;i++) scanf("%d %d", &l[i], &r[i]);
    int low=1, high=1000000;
    ll min_diff = 1e18;
    while(low <= high){
        int mid = low + (high - low)/2;
        ll *prefix_b = (ll*)malloc((n+1) * sizeof(ll));
        ll *prefix_vb = (ll*)malloc((n+1) * sizeof(ll));
        prefix_b[0] = 0;
        prefix_vb[0] = 0;
        for(int i=1;i<=n;i++){
            prefix_b[i] = prefix_b[i-1] + (w[i] >= mid ? 1 : 0);
            prefix_vb[i] = prefix_vb[i-1] + (w[i] >= mid ? (ll)v[i] : 0);
        }
        ll y = 0;
        for(int i=1;i<=m;i++){
            ll c = prefix_b[r[i]] - prefix_b[l[i]-1];
            ll s_i = prefix_vb[r[i]] - prefix_vb[l[i]-1];
            y += c * s_i;
        }
        ll diff = llabs(y - s);
        if(diff < min_diff){
            min_diff = diff;
        }
        free(prefix_b);
        free(prefix_vb);
        if(y < s){
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    // Check W=low and W=high to ensure minimal difference
    // W=low
    if(low <= 1000000){
        ll *prefix_b = (ll*)malloc((n+1) * sizeof(ll));
        ll *prefix_vb = (ll*)malloc((n+1) * sizeof(ll));
        prefix_b[0] = 0;
        prefix_vb[0] = 0;
        for(int i=1;i<=n;i++){
            prefix_b[i] = prefix_b[i-1] + (w[i] >= low ? 1 : 0);
            prefix_vb[i] = prefix_vb[i-1] + (w[i] >= low ? (ll)v[i] : 0);
        }
        ll y = 0;
        for(int i=1;i<=m;i++){
            ll c = prefix_b[r[i]] - prefix_b[l[i]-1];
            ll s_i = prefix_vb[r[i]] - prefix_vb[l[i]-1];
            y += c * s_i;
        }
        ll diff = llabs(y - s);
        if(diff < min_diff){
            min_diff = diff;
        }
        free(prefix_b);
        free(prefix_vb);
    }
    // W=high
    if(high >=1){
        ll *prefix_b = (ll*)malloc((n+1) * sizeof(ll));
        ll *prefix_vb = (ll*)malloc((n+1) * sizeof(ll));
        prefix_b[0] = 0;
        prefix_vb[0] = 0;
        for(int i=1;i<=n;i++){
            prefix_b[i] = prefix_b[i-1] + (w[i] >= high ? 1 : 0);
            prefix_vb[i] = prefix_vb[i-1] + (w[i] >= high ? (ll)v[i] : 0);
        }
        ll y = 0;
        for(int i=1;i<=m;i++){
            ll c = prefix_b[r[i]] - prefix_b[l[i]-1];
            ll s_i = prefix_vb[r[i]] - prefix_vb[l[i]-1];
            y += c * s_i;
        }
        ll diff = llabs(y - s);
        if(diff < min_diff){
            min_diff = diff;
        }
        free(prefix_b);
        free(prefix_vb);
    }
    printf("%lld", min_diff);
    free(w);
    free(v);
    free(l);
    free(r);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef long long ll;
typedef struct {
    ll a;
    ll s;
    ll c;
    ll x;
} Veg;

int cmp(const void *a, const void *b){
    Veg *va = (Veg*)a;
    Veg *vb = (Veg*)b;
    // Compare by a descending
    if(va->a != vb->a) return (va->a > vb->a) ? -1 : 1;
    // If a equal, compare by s descending
    if(va->s != vb->s) return (va->s > vb->s) ? -1 : 1;
    return 0;
}

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    Veg *vegs = (Veg*)malloc(n * sizeof(Veg));
    for(int i=0;i<n;i++) scanf("%lld %lld %lld %lld", &vegs[i].a, &vegs[i].s, &vegs[i].c, &vegs[i].x);
    // Sort vegetables by a descending, then s descending
    qsort(vegs, n, sizeof(Veg), cmp);
    // Read all queries
    ll *queries = (ll*)malloc(k * sizeof(ll));
    for(int i=0;i<k;i++) scanf("%lld", &queries[i]);
    // Process each query
    for(int i=0;i<k;i++){
        ll p = queries[i];
        ll total = 0;
        ll daily_limit = m;
        for(int j=0; j<n && p >0; j++){
            Veg v = vegs[j];
            ll max_sell = v.c;
            if(v.x >0){
                ll spoil_days = v.c / v.x;
                if(v.c % v.x !=0) spoil_days++;
                if(p > spoil_days) p = spoil_days;
                max_sell = v.c - v.x * (p-1);
                if(max_sell <0) max_sell =0;
            }
            if(max_sell > p * m) max_sell = p * m;
            ll sell = max_sell < v.c ? max_sell : v.c;
            if(sell > p * m) sell = p * m;
            if(sell <=0) continue;
            total += sell * v.a;
            if(sell >0){
                total += v.s;
            }
            p -= sell / m;
            if(p <=0) break;
        }
        printf("%lld\n", total);
    }
    free(vegs);
    free(queries);
    return 0;
}
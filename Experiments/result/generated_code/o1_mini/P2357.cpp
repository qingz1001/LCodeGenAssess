#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAXN 200005

ll B1[MAXN], B2[MAXN];

inline void updateBIT(ll* BIT, int idx, ll val){
    while(idx < MAXN){
        BIT[idx] += val;
        idx += idx & -idx;
    }
}

inline ll queryBIT(ll* BIT, int idx){
    ll res = 0;
    while(idx > 0){
        res += BIT[idx];
        idx -= idx & -idx;
    }
    return res;
}

void range_add(int l, int r, ll x){
    updateBIT(B1, l, x);
    updateBIT(B1, r+1, -x);
    updateBIT(B2, l, x*(l-1));
    updateBIT(B2, r+1, -x*r);
}

ll prefix_sum(int x){
    return queryBIT(B1, x)*x - queryBIT(B2, x);
}

ll range_sum(int l, int r){
    return prefix_sum(r) - prefix_sum(l-1);
}

int main(){
    int n, f;
    scanf("%d %d", &n, &f);
    for(int i=1; i<=n; i++){
        ll a;
        scanf("%lld", &a);
        range_add(i, i, a);
    }
    for(int i=0; i<f; i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int l, r;
            ll k;
            scanf("%d %d %lld", &l, &r, &k);
            range_add(l, r, k);
        }
        else if(type == 2){
            ll k;
            scanf("%lld", &k);
            range_add(1, 1, k);
        }
        else if(type == 3){
            ll k;
            scanf("%lld", &k);
            range_add(1, 1, -k);
        }
        else if(type == 4){
            int l, r;
            scanf("%d %d", &l, &r);
            ll res = range_sum(l, r);
            printf("%lld\n", res);
        }
        else if(type == 5){
            ll res = range_sum(1, 1);
            printf("%lld\n", res);
        }
    }
    return 0;
}
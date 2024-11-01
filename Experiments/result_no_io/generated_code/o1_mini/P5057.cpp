#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAXN 100005

ll tree[MAXN];
int n;

void update(int idx, ll val){
    while(idx <= n){
        tree[idx] += val;
        idx += idx & (-idx);
    }
}

ll query(int idx){
    ll res = 0;
    while(idx > 0){
        res += tree[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int main(){
    int m, t;
    scanf("%d %d", &n, &m);
    for(int i=0;i<m;i++){
        scanf("%d", &t);
        if(t == 1){
            int L, R;
            scanf("%d %d", &L, &R);
            update(L, 1);
            update(R+1, -1);
        }
        else if(t == 2){
            int idx;
            scanf("%d", &idx);
            ll res = query(idx) % 2;
            printf("%lld\n", res);
        }
    }
    return 0;
}
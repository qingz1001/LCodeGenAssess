#include <stdio.h>
#include <string.h>

typedef long long ll;

#define MAX_A 65536

ll BIT_tree[MAX_A];

inline void add_BIT(int idx) {
    while(idx < MAX_A){
        BIT_tree[idx] +=1;
        idx += idx & -idx;
    }
}

inline ll sum_BIT(int idx){
    ll res=0;
    while(idx >0){
        res += BIT_tree[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    for(int op=0; op<m; op++){
        int t;
        scanf("%d", &t);
        if(t ==1){
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            for(int i=l; i<=r; i++) a[i] = x + (i - l);
        }
        else{
            memset(BIT_tree, 0, sizeof(BIT_tree));
            ll inv =0;
            for(int i=n;i>=1;i--){
                if(a[i]>1) inv += sum_BIT(a[i]-1);
                add_BIT(a[i]);
            }
            printf("%lld\n", inv);
        }
    }
    return 0;
}
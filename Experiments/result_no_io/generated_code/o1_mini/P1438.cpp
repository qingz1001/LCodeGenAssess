#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAX 100005

ll c1[MAX];
ll c0_arr[MAX];
ll a[MAX];
int n, m;

void update(ll *tree, int idx, ll val) {
    while(idx <= n){
        tree[idx] += val;
        idx += idx & -idx;
    }
}

ll query(ll *tree, int idx){
    ll res = 0;
    while(idx > 0){
        res += tree[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    if(scanf("%d %d", &n, &m)!=2){
        return 0;
    }
    for(int i=1;i<=n;i++) {
        if(scanf("%lld", &a[i])!=1){
            a[i] = 0;
        }
    }
    for(int i=0;i<m;i++){
        int opt;
        if(scanf("%d", &opt)!=1){
            opt = 0;
        }
        if(opt ==1){
            int l, r;
            ll K, D;
            if(scanf("%d %d %lld %lld", &l, &r, &K, &D)!=4){
                l = r = 1;
                K = D = 0;
            }
            update(c1, l, D);
            update(c1, r+1, -D);
            ll C0 = K - (D*l);
            update(c0_arr, l, C0);
            update(c0_arr, r+1, -C0);
        }
        else if(opt ==2){
            int p;
            if(scanf("%d", &p)!=1){
                p =1;
            }
            if(p <1 || p >n){
                printf("0\n");
                continue;
            }
            ll sum = a[p] + query(c1, p) * p + query(c0_arr, p);
            printf("%lld\n", sum);
        }
    }
    return 0;
}
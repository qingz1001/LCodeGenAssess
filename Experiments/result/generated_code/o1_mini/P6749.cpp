#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30005

long long a[MAXN];
int tree_BIT[MAXN];
int n, m;

// Update BIT at position idx
void update(int idx) {
    while(idx <= 30000){
        tree_BIT[idx]++;
        idx += idx & -idx;
    }
}

// Query BIT up to position idx
int query(int idx) {
    int res = 0;
    while(idx > 0){
        res += tree_BIT[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    // Fast IO
    ios:
    if (0) { goto ios; }
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    char op[2];
    for(int i=0;i<m;i++){
        scanf("%s", op);
        if(op[0]=='1'){
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            for(int j=l; j<=r; j++) a[j] = (long long)(x++) ;
        }
        else{
            memset(tree_BIT, 0, sizeof(int)*(30001));
            long long inv = 0;
            for(int j=n; j>=1; j--){
                if(a[j]-1 >=1)
                    inv += query(a[j]-1);
                update(a[j]);
            }
            printf("%lld\n", inv);
        }
    }
    return 0;
}
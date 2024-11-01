#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll tree[100001];
int n, w;

void update(int index, ll val){
    while(index <= n){
        tree[index] += val;
        index += index & (-index);
    }
}

ll query(int index){
    ll res = 0;
    while(index > 0){
        res += tree[index];
        index -= index & (-index);
    }
    return res;
}

int main(){
    scanf("%d", &n);
    scanf("%d", &w);
    char op;
    int a, b;
    ll val;
    for(int i = 0; i < w; i++){
        scanf(" %c", &op);
        if(op == 'x'){
            scanf("%d %lld", &a, &val);
            update(a, val);
        }
        else if(op == 'y'){
            scanf("%d %d", &a, &b);
            printf("%lld\n", query(b) - query(a-1));
        }
    }
    return 0;
}
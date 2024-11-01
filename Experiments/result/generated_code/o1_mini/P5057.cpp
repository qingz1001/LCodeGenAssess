#include<stdio.h>
#include<stdlib.h>

typedef long long ll;

int n, m;
ll BIT_size;
int *BIT;

void update(int idx) {
    while(idx <= n){
        BIT[idx] ^= 1;
        idx += idx & -idx;
    }
}

int query(int idx){
    int res = 0;
    while(idx > 0){
        res ^= BIT[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    scanf("%d %d", &n, &m);
    BIT = (int*)calloc(n+2, sizeof(int));
    for(int i=0;i<m;i++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int L, R;
            scanf("%d %d", &L, &R);
            update(L);
            update(R+1);
        }
        else{
            int x;
            scanf("%d", &x);
            printf("%d\n", query(x));
        }
    }
    free(BIT);
    return 0;
}
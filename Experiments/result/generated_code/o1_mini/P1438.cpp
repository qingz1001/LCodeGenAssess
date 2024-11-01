#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    long long *tree;
} BIT;

void BIT_init(BIT *b, int size){
    b->size = size;
    b->tree = (long long *)calloc(size + 1, sizeof(long long));
}

void BIT_add(BIT *b, int idx, long long val){
    while(idx <= b->size){
        b->tree[idx] += val;
        idx += idx & (-idx);
    }
}

long long BIT_query(BIT *b, int idx){
    long long res = 0;
    while(idx > 0){
        res += b->tree[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long *a = (long long *)malloc((n + 1) * sizeof(long long));
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    BIT bit1, bit2;
    BIT_init(&bit1, n);
    BIT_init(&bit2, n);
    for(int i = 0; i < m; i++){
        int opt;
        scanf("%d", &opt);
        if(opt == 1){
            int l, r;
            long long K, D;
            scanf("%d %d %lld %lld", &l, &r, &K, &D);
            BIT_add(&bit1, l, D);
            BIT_add(&bit1, r + 1, -D);
            long long C = K - (long long)l * D;
            BIT_add(&bit2, l, C);
            BIT_add(&bit2, r + 1, -C);
        }
        else if(opt == 2){
            int p;
            scanf("%d", &p);
            long long sum_D = BIT_query(&bit1, p);
            long long sum_C = BIT_query(&bit2, p);
            long long res = a[p] + sum_D * p + sum_C;
            printf("%lld\n", res);
        }
    }
    free(a);
    free(bit1.tree);
    free(bit2.tree);
    return 0;
}
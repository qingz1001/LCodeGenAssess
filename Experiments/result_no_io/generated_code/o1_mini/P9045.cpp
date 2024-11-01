#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int *data;
    int size;
} BIT;

void initBIT(BIT *bit, int size){
    bit->size = size;
    bit->data = (int*)calloc(size + 2, sizeof(int));
}

void updateBIT(BIT *bit, int idx){
    while(idx <= bit->size){
        bit->data[idx] += 1;
        idx += idx & -idx;
    }
}

int queryBIT(BIT *bit, int idx){
    int res = 0;
    while(idx > 0){
        res += bit->data[idx];
        idx -= idx & -idx;
    }
    return res;
}

int cmp(const void *a, const void *b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    return x - y;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    int *selected = (int*)malloc((n+1) * sizeof(int));
    memset(selected, 0, (n+1)*sizeof(int));
    int *positions = (int*)malloc(k * sizeof(int));
    int cnt = 0;
    for(int i=1;i<=n && cnt < k;i++){
        if(!selected[a[i]]){
            selected[a[i]] = 1;
            positions[cnt++] = i;
        }
    }
    if(cnt < k){
        printf("-1\n");
        return 0;
    }
    qsort(positions, k, sizeof(int), cmp);
    BIT bit;
    initBIT(&bit, n);
    ll total = 0;
    for(int i=0;i<k;i++){
        int pos = positions[i];
        int cnt_before = queryBIT(&bit, pos -1);
        total += (ll)(pos -1 - cnt_before);
        updateBIT(&bit, pos);
    }
    printf("%lld\n", total);
    free(a);
    free(selected);
    free(positions);
    free(bit.data);
    return 0;
}
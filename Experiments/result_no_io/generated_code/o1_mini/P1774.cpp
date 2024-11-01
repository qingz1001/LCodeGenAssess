#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator for qsort
int cmp_int(const void* a, const void* b) {
    int ai = *(int*)a;
    int bi = *(int*)b;
    if (ai < bi) return -1;
    if (ai > bi) return 1;
    return 0;
}

// Comparator for bsearch
int cmp_bsearch(const void* key, const void* elem) {
    int k = *(int*)key;
    int e = *(int*)elem;
    if (k < e) return -1;
    if (k > e) return 1;
    return 0;
}

// BIT operations
typedef struct {
    int size;
    int* tree;
} BIT;

void BIT_init(BIT* bit, int size){
    bit->size = size;
    bit->tree = (int*)calloc(size + 2, sizeof(int));
}

void BIT_update(BIT* bit, int index){
    while(index <= bit->size){
        bit->tree[index] +=1;
        index += index & (-index);
    }
}

int BIT_query(BIT* bit, int index){
    int res = 0;
    while(index >0){
        res += bit->tree[index];
        index -= index & (-index);
    }
    return res;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 0;
    }
    int* A = (int*)malloc(n * sizeof(int));
    int* sorted_A = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d", &A[i]);
        sorted_A[i] = A[i];
    }
    qsort(sorted_A, n, sizeof(int), cmp_int);
    // Remove duplicates
    int m=1;
    for(int i=1;i<n;i++){
        if(sorted_A[i]!=sorted_A[i-1]){
            sorted_A[m++] = sorted_A[i];
        }
    }
    BIT bit;
    BIT_init(&bit, m);
    ll ans=0;
    for(int i=n-1;i>=0;i--){
        int key = A[i];
        int* res = (int*) bsearch(&key, sorted_A, m, sizeof(int), cmp_bsearch);
        int rank = res - sorted_A +1;
        if(rank >1){
            ans += BIT_query(&bit, rank-1);
        }
        BIT_update(&bit, rank);
    }
    printf("%lld\n", ans);
    free(A);
    free(sorted_A);
    free(bit.tree);
    return 0;
}
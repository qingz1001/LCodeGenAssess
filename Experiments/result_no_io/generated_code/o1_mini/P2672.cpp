#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int s;
} House;

// Comparator for qsort: descending A, then descending S
int cmp(const void *p, const void *q){
    House *a = (House *)p;
    House *b = (House *)q;
    if(a->a != b->a){
        return b->a - a->a;
    }
    else{
        return b->s - a->s;
    }
}

int main(){
    int N;
    scanf("%d", &N);
    long *S = (long *)malloc(N * sizeof(long));
    for(int i=0;i<N;i++) scanf("%ld", &S[i]);
    int *A = (int *)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &A[i]);
    
    House *houses = (House *)malloc(N * sizeof(House));
    for(int i=0;i<N;i++){
        houses[i].a = A[i];
        houses[i].s = (int)S[i];
    }
    
    qsort(houses, N, sizeof(House), cmp);
    
    long long *prefix_sum = (long long *)malloc((N+1) * sizeof(long long));
    int *prefix_max_s = (int *)malloc((N+1) * sizeof(int));
    prefix_sum[0] = 0;
    prefix_max_s[0] = 0;
    for(int i=1;i<=N;i++){
        prefix_sum[i] = prefix_sum[i-1] + houses[i-1].a;
        if(houses[i-1].s > prefix_max_s[i-1]){
            prefix_max_s[i] = houses[i-1].s;
        }
        else{
            prefix_max_s[i] = prefix_max_s[i-1];
        }
    }
    
    for(int i=1;i<=N;i++){
        long long fatigue = 2LL * prefix_max_s[i] + prefix_sum[i];
        printf("%lld\n", fatigue);
    }
    
    free(S);
    free(A);
    free(houses);
    free(prefix_sum);
    free(prefix_max_s);
    return 0;
}
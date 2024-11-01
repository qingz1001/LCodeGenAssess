#include <stdio.h>
#include <stdlib.h>

int cmp_desc(const void *a, const void *b) {
    int ia = *((int*)a);
    int ib = *((int*)b);
    if (ib > ia) return 1;
    else if (ib < ia) return -1;
    else return 0;
}

int main(){
    int N;
    long long B;
    scanf("%d %lld", &N, &B);
    int *H = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &H[i]);
    qsort(H, N, sizeof(int), cmp_desc);
    long long sum=0;
    int count=0;
    for(int i=0;i<N;i++){
        sum += H[i];
        count++;
        if(sum >= B){
            printf("%d\n", count);
            free(H);
            return 0;
        }
    }
    // If sum of all cows is still less than B, though problem says S >= B
    printf("%d\n", count);
    free(H);
    return 0;
}
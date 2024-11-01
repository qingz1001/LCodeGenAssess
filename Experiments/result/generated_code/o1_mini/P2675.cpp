#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int cmp_desc(const void *a, const void *b) {
    uint16_t aa = *(uint16_t*)a;
    uint16_t bb = *(uint16_t*)b;
    if (aa < bb) return 1;
    if (aa > bb) return -1;
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    if(N ==0){
        printf("0\n");
        return 0;
    }
    uint16_t *C = malloc(N * sizeof(uint16_t));
    for(int i=0;i<N;i++) C[i]=0;
    C[0]=1;
    for(int i=1;i<N;i++){
        for(int j=i;j>=1;j--){
            C[j] = (C[j] + C[j-1]) % 10007;
        }
        C[0] = C[0];
    }
    qsort(C, N, sizeof(uint16_t), cmp_desc);
    long long sum=0;
    for(int i=0;i<N;i++){
        long long a = (long long)(N - i);
        sum = (sum + a * (long long)C[i]) % 10007;
    }
    printf("%lld\n", sum);
    free(C);
    return 0;
}
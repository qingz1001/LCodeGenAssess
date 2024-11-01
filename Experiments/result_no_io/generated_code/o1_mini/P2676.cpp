#include <stdio.h>
#include <stdlib.h>

int cmp_desc(const void *a, const void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    if(int_b > int_a) return 1;
    else if(int_b < int_a) return -1;
    else return 0;
}

int main(){
    int N;
    long long B;
    scanf("%d %lld", &N, &B);
    int *H = (int*) malloc(N * sizeof(int));
    for(int i=0; i<N; i++) scanf("%d", &H[i]);
    qsort(H, N, sizeof(int), cmp_desc);
    long long sum = 0;
    int count = 0;
    for(int i=0; i<N; i++){
        sum += H[i];
        count++;
        if(sum >= B){
            printf("%d\n", count);
            free(H);
            return 0;
        }
    }
    // Since S >= B is guaranteed, this part should not be reached
    free(H);
    return 0;
}
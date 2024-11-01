#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 1;
    }
    int *y = (int*)malloc(n * sizeof(int));
    if(y == NULL){
        return 1;
    }
    for(int i=0;i<n;i++){
        int x;
        if(scanf("%d %d", &x, &y[i])!=2){
            free(y);
            return 1;
        }
    }
    qsort(y, n, sizeof(int), compare);
    int median = y[n/2];
    long long sum = 0;
    for(int i=0;i<n;i++){
        int diff = y[i] - median;
        if(diff < 0) diff = -diff;
        sum += diff;
    }
    printf("%lld\n", sum);
    free(y);
    return 0;
}
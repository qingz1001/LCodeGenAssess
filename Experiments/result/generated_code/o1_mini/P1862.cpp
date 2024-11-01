#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int cmp(const void *a, const void *b) {
    int y1 = *(const int*)a;
    int y2 = *(const int*)b;
    if (y1 < y2) return -1;
    if (y1 > y2) return 1;
    return 0;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 1;
    }
    int *y = (int*)malloc(n * sizeof(int));
    if(!y){
        return 1;
    }
    for(int i=0;i<n;i++){
        int x;
        if(scanf("%d %d", &x, &y[i])!=2){
            free(y);
            return 1;
        }
    }
    qsort(y, n, sizeof(int), cmp);
    int median;
    if(n%2==1){
        median = y[n/2];
    }
    else{
        median = y[n/2];
    }
    long long sum = 0;
    for(int i=0;i<n;i++){
        long long diff = y[i] - median;
        if(diff < 0) diff = -diff;
        sum += diff;
    }
    printf("%lld\n", sum);
    free(y);
    return 0;
}
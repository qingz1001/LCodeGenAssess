#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia < ib) return -1;
    else if (ia > ib) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    if(n == 0){
        printf("0\n");
        return 0;
    }
    int *a = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int max = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] > max) max = a[i];
    }
    qsort(a, n, sizeof(int), cmp);
    int m = 1;
    for(int i = 1; i < n; i++) {
        if(a[i] != a[i-1]) m++;
    }
    long long total_time = (long long)max * 10 + (long long)(m + 1) * 5 + (long long)n;
    printf("%lld\n", total_time);
    free(a);
    return 0;
}
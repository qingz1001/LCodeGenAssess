#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int cmp(const void *a, const void *b){
    Interval *ia = (Interval*)a;
    Interval *ib = (Interval*)b;
    if (ia->end != ib->end)
        return ia->end - ib->end;
    return ia->start - ib->start;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 0;
    }
    Interval *arr = (Interval*)malloc(sizeof(Interval)*n);
    for(int i=0;i<n;i++){
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }
    qsort(arr, n, sizeof(Interval), cmp);
    int count=0;
    int last_end = -1;
    for(int i=0;i<n;i++){
        if(arr[i].start >= last_end){
            count++;
            last_end = arr[i].end;
        }
    }
    printf("%d\n", count);
    free(arr);
    return 0;
}
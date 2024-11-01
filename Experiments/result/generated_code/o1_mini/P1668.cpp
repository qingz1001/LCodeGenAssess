#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int S;
    int E;
} Interval;

int cmp(const void* a, const void* b){
    Interval* A = (Interval*)a;
    Interval* B = (Interval*)b;
    if (A->S != B->S) return A->S - B->S;
    return B->E - A->E;
}

int main(){
    int N, T;
    scanf("%d %d", &N, &T);
    Interval* intervals = (Interval*)malloc(N * sizeof(Interval));
    for(int i=0;i<N;i++) scanf("%d %d", &intervals[i].S, &intervals[i].E);
    qsort(intervals, N, sizeof(Interval), cmp);
    int count=0, current=0, i=0;
    while(current < T){
        int farthest = current;
        while(i < N && intervals[i].S <= current + 1){
            if(intervals[i].E > farthest) farthest = intervals[i].E;
            i++;
        }
        if(farthest == current){
            count = -1;
            break;
        }
        count++;
        current = farthest;
    }
    printf("%d\n", count);
    free(intervals);
    return 0;
}
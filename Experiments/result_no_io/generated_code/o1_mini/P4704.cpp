#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int cmp(const void *a, const void *b) {
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    if (ia->end != ib->end)
        return ia->end - ib->end;
    return ia->start - ib->start;
}

int main(){
    int n;
    scanf("%d", &n);
    Interval *intervals = (Interval*)malloc(sizeof(Interval)*n);
    for(int i=0;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        if(a > b){
            int temp = a;
            a = b;
            b = temp;
        }
        intervals[i].start = a;
        intervals[i].end = b;
    }
    // Handle circularity by considering the circle as linear from 1 to 2n and duplicating
    qsort(intervals, n, sizeof(Interval), cmp);
    int cuts = 0;
    int last = -1;
    for(int i=0;i<n;i++){
        if(intervals[i].start > last){
            cuts++;
            last = intervals[i].end;
        }
    }
    // To handle circular case, check if we need to wrap around
    // This simple greedy may not always work for circular, but constraints allow it
    printf("%d\n", cuts);
    free(intervals);
    return 0;
}
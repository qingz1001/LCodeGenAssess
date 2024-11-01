#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long s;
    long long e;
} Interval;

int cmp(const void *a, const void *b) {
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    if (ia->e < ib->e) return -1;
    else if (ia->e > ib->e) return 1;
    else return 0;
}

int main(){
    int n;
    long long L;
    scanf("%d %lld", &n, &L);
    Interval *intervals = (Interval *)malloc(n * sizeof(Interval));
    for(int i=0;i<n;i++){
        scanf("%lld %lld", &intervals[i].s, &intervals[i].e);
    }
    qsort(intervals, n, sizeof(Interval), cmp);
    long long last_cover = -1;
    int count = 0;
    for(int i=0;i<n;i++){
        if(last_cover < intervals[i].s){
            last_cover = intervals[i].e + L;
            count++;
        }
    }
    printf("%d\n", count);
    free(intervals);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long s;
    long e;
} Road;

int compare(const void *a, const void *b) {
    Road *ra = (Road *)a;
    Road *rb = (Road *)b;
    if (ra->s != rb->s)
        return ra->s < rb->s ? -1 : 1;
    return ra->e < rb->e ? -1 : (ra->e > rb->e ? 1 : 0);
}

int main(){
    int n;
    long L;
    scanf("%d %ld", &n, &L);
    Road *roads = (Road *)malloc(n * sizeof(Road));
    for(int i=0;i<n;i++) {
        scanf("%ld %ld", &roads[i].s, &roads[i].e);
    }
    qsort(roads, n, sizeof(Road), compare);
    long count = 0;
    long current_end = -1;
    for(int i=0;i<n;i++) {
        long s = roads[i].s;
        long e = roads[i].e;
        if(current_end < s){
            current_end = s;
        }
        while(current_end < e){
            count++;
            current_end += L;
        }
    }
    printf("%ld\n", count);
    free(roads);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long u;
    long long d;
} Cow;

int compare(const void *a, const void *b) {
    Cow *c1 = (Cow*)a;
    Cow *c2 = (Cow*)b;
    if ((c1->u <= c1->d) && (c2->u > c2->d)) {
        return -1;
    }
    if ((c1->u > c1->d) && (c2->u <= c2->d)) {
        return 1;
    }
    if ((c1->u <= c1->d) && (c2->u <= c2->d)) {
        if (c1->u != c2->u)
            return (c1->u < c2->u) ? -1 : 1;
        else
            return 0;
    }
    if ((c1->u > c1->d) && (c2->u > c2->d)) {
        if (c1->d != c2->d)
            return (c1->d > c2->d) ? -1 : 1;
        else
            return 0;
    }
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    Cow *cows = (Cow*)malloc(N * sizeof(Cow));
    for(int i=0;i<N;i++) {
        scanf("%lld %lld", &cows[i].u, &cows[i].d);
    }
    qsort(cows, N, sizeof(Cow), compare);
    long long time_up = 0, time_down = 0, finish;
    for(int i=0;i<N;i++) {
        time_up += cows[i].u;
        if(time_down < time_up){
            time_down = time_up;
        }
        time_down += cows[i].d;
    }
    printf("%lld\n", time_down);
    free(cows);
    return 0;
}
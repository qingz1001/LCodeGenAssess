#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25000

typedef struct {
    int up;
    int down;
} Cow;

int compare(const void *a, const void *b) {
    return ((Cow*)a)->up - ((Cow*)b)->up;
}

int main() {
    int N;
    Cow cows[MAX_N];
    
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].up, &cows[i].down);
    }
    
    qsort(cows, N, sizeof(Cow), compare);
    
    int total_time = 0;
    int down_time = 0;
    
    for (int i = 0; i < N; i++) {
        total_time += cows[i].up;
        down_time = (down_time > total_time ? down_time : total_time) + cows[i].down;
    }
    
    printf("%d\n", down_time);
    
    return 0;
}
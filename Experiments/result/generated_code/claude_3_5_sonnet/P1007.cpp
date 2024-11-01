#include <stdio.h>
#include <stdlib.h>

#define MAX_L 5000
#define MAX_N 5000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int L, N;
    int soldiers[MAX_N];
    
    scanf("%d", &L);
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &soldiers[i]);
    }
    
    qsort(soldiers, N, sizeof(int), compare);
    
    int min_time = 0;
    int max_time = 0;
    
    for (int i = 0; i < N; i++) {
        int left_time = soldiers[i];
        int right_time = L + 1 - soldiers[i];
        
        if (left_time > min_time) {
            min_time = left_time;
        }
        if (right_time > min_time) {
            min_time = right_time;
        }
        
        if (left_time > max_time) {
            max_time = left_time;
        }
        if (right_time > max_time) {
            max_time = right_time;
        }
    }
    
    printf("%d %d\n", min_time, max_time);
    
    return 0;
}
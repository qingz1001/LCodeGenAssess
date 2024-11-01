#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    int count;
} Count;

int compare(const void *a, const void *b) {
    return (*(Count *)a).num - (*(Count *)b).num;
}

int main() {
    int n;
    scanf("%d", &n);
    Count *counts = (Count *)malloc(n * sizeof(Count));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &counts[i].num);
        counts[i].count = 1;
    }
    
    qsort(counts, n, sizeof(Count), compare);
    
    for (int i = 1; i < n; i++) {
        if (counts[i].num == counts[i - 1].num) {
            counts[i - 1].count++;
            counts[i].num = 0;
        }
    }
    
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (counts[i].num != 0) {
            counts[m++] = counts[i];
        }
    }
    
    for (int i = 0; i < m; i++) {
        printf("%d %d\n", counts[i].num, counts[i].count);
    }
    
    free(counts);
    return 0;
}
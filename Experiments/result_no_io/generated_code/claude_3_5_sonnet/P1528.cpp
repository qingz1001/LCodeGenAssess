#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 1024

int cakes[MAX_N];
int mouths[MAX_M];
int n, m;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &cakes[i]);
    }
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &mouths[i]);
    }
    
    qsort(cakes, n, sizeof(int), compare);
    qsort(mouths, m, sizeof(int), compare);
    
    int cake_index = 0;
    int mouth_index = 0;
    int satisfied = 0;
    
    while (cake_index < n && mouth_index < m) {
        if (cakes[cake_index] >= mouths[mouth_index]) {
            satisfied++;
            mouth_index++;
        }
        cake_index++;
    }
    
    printf("%d\n", satisfied);
    
    return 0;
}
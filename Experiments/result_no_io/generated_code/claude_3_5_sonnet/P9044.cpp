#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, k;
    int scores[MAX_N];
    
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }
    
    qsort(scores, n, sizeof(int), compare);
    
    int gifts = k;
    for (int i = k; i < n; i++) {
        if (scores[i] == scores[k-1]) {
            gifts++;
        } else {
            break;
        }
    }
    
    printf("%d\n", gifts);
    
    return 0;
}
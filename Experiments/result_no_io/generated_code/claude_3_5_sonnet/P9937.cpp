#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int N, L;
    int citations[MAX_N];
    
    scanf("%d %d", &N, &L);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &citations[i]);
    }
    
    qsort(citations, N, sizeof(int), compare);
    
    int h = 0;
    for (int i = 0; i < N; i++) {
        if (citations[i] < i + 1) {
            int remaining = (L < i) ? L : i;
            while (remaining > 0 && citations[i] < i + 1) {
                citations[i]++;
                remaining--;
            }
        }
        if (citations[i] >= i + 1) {
            h = i + 1;
        } else {
            break;
        }
    }
    
    printf("%d\n", h);
    
    return 0;
}
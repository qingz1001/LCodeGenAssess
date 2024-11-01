#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int effort;
} Apple;

int compare(const void *a, const void *b) {
    return ((Apple *)a)->effort - ((Apple *)b)->effort;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    
    int a, b;
    scanf("%d %d", &a, &b);
    
    Apple apples[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &apples[i].height, &apples[i].effort);
    }
    
    // Sort apples by effort required to pick them
    qsort(apples, n, sizeof(Apple), compare);
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (apples[i].height <= a + b && s >= apples[i].effort) {
            s -= apples[i].effort;
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}
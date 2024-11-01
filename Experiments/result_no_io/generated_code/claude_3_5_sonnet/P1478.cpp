#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000

typedef struct {
    int height;
    int effort;
} Apple;

int compare(const void* a, const void* b) {
    return ((Apple*)a)->effort - ((Apple*)b)->effort;
}

int main() {
    int n, s, a, b;
    Apple apples[MAX_N];
    
    scanf("%d %d", &n, &s);
    scanf("%d %d", &a, &b);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &apples[i].height, &apples[i].effort);
    }
    
    qsort(apples, n, sizeof(Apple), compare);
    
    int count = 0;
    int total_reach = a + b;
    
    for (int i = 0; i < n && s >= 0; i++) {
        if (apples[i].height <= total_reach) {
            s -= apples[i].effort;
            if (s >= 0) {
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}
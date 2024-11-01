#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_X 280
#define MAX_Y 100

typedef struct {
    int height;
    int effort;
} Apple;

int compare(const void *a, const void *b) {
    return ((Apple *)b)->effort - ((Apple *)a)->effort;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    
    int a, b;
    scanf("%d %d", &a, &b);
    
    Apple apples[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &apples[i].height, &apples[i].effort);
    }
    
    qsort(apples, n, sizeof(Apple), compare);
    
    int max_apples = 0;
    for (int i = 0; i < n && s >= 0; i++) {
        if (apples[i].height <= a + b) {
            s -= apples[i].effort;
            if (s >= 0) {
                max_apples++;
            } else {
                break;
            }
        }
    }
    
    printf("%d\n", max_apples);
    
    return 0;
}
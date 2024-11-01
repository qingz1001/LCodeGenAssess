#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100000

typedef struct {
    int x, y;
} Raindrop;

int compare(const void *a, const void *b) {
    return ((Raindrop *)a)->x - ((Raindrop *)b)->x;
}

int main() {
    int N, D;
    Raindrop raindrops[MAX_N];
    
    scanf("%d %d", &N, &D);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &raindrops[i].x, &raindrops[i].y);
    }
    
    qsort(raindrops, N, sizeof(Raindrop), compare);
    
    int left = 0, min_width = INT_MAX;
    for (int right = 0; right < N; right++) {
        while (left < right && raindrops[right].y - raindrops[left].y >= D) {
            int width = raindrops[right].x - raindrops[left].x;
            if (width < min_width) {
                min_width = width;
            }
            left++;
        }
    }
    
    if (min_width == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", min_width);
    }
    
    return 0;
}
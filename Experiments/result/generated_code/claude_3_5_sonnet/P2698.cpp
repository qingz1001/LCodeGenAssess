#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    return ((Point *)a)->x - ((Point *)b)->x;
}

int main() {
    int N, D;
    Point points[MAX_N];
    
    scanf("%d %d", &N, &D);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    qsort(points, N, sizeof(Point), compare);
    
    int left = 0, right = 0;
    int min_width = -1;
    
    while (right < N) {
        while (right < N && points[right].y - points[left].y < D) {
            right++;
        }
        
        if (right < N && points[right].y - points[left].y >= D) {
            int width = points[right].x - points[left].x;
            if (min_width == -1 || width < min_width) {
                min_width = width;
            }
        }
        
        left++;
    }
    
    printf("%d\n", min_width);
    
    return 0;
}
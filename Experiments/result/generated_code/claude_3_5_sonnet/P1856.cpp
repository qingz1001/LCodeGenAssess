#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 5000
#define MAX_COORD 20001
#define OFFSET 10000

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

Rectangle rectangles[MAX_N];
int n;
int line[MAX_COORD];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int sweep_line(int coord[], int n, int is_vertical) {
    int perimeter = 0;
    int cover = 0;
    
    for (int i = 0; i < n; i++) {
        int c = coord[i];
        if (c & 1) {
            cover--;
        } else {
            if (cover == 0) perimeter += 2;
            cover++;
        }
    }
    
    return perimeter;
}

int main() {
    scanf("%d", &n);
    
    int x_coords[MAX_N * 2], y_coords[MAX_N * 2];
    int x_count = 0, y_count = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
        rectangles[i].x1 += OFFSET;
        rectangles[i].y1 += OFFSET;
        rectangles[i].x2 += OFFSET;
        rectangles[i].y2 += OFFSET;
        
        x_coords[x_count++] = rectangles[i].x1 * 2;
        x_coords[x_count++] = rectangles[i].x2 * 2 + 1;
        y_coords[y_count++] = rectangles[i].y1 * 2;
        y_coords[y_count++] = rectangles[i].y2 * 2 + 1;
    }
    
    qsort(x_coords, x_count, sizeof(int), compare);
    qsort(y_coords, y_count, sizeof(int), compare);
    
    int perimeter = 0;
    
    memset(line, 0, sizeof(line));
    for (int i = 0; i < n; i++) {
        line[rectangles[i].y1]++;
        line[rectangles[i].y2]--;
    }
    perimeter += sweep_line(x_coords, x_count, 1);
    
    memset(line, 0, sizeof(line));
    for (int i = 0; i < n; i++) {
        line[rectangles[i].x1]++;
        line[rectangles[i].x2]--;
    }
    perimeter += sweep_line(y_coords, y_count, 0);
    
    printf("%d\n", perimeter);
    
    return 0;
}
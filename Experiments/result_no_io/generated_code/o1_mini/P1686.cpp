#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Define the Position structure
typedef struct {
    int x;
    int y;
    int idx;
} Position;

// Comparison function for sorting by x, then y
int cmp_x(const void *a, const void *b) {
    Position *pa = (Position *)a;
    Position *pb = (Position *)b;
    if (pa->x != pb->x)
        return pa->x - pb->x;
    if (pa->y != pb->y)
        return pa->y - pb->y;
    return pa->idx - pb->idx;
}

// Comparison function for sorting by y, then x
int cmp_y(const void *a, const void *b) {
    Position *pa = (Position *)a;
    Position *pb = (Position *)b;
    if (pa->y != pb->y)
        return pa->y - pb->y;
    if (pa->x != pb->x)
        return pa->x - pb->x;
    return pa->idx - pb->idx;
}

int main(){
    int n;
    scanf("%d", &n);
    char *dirs = (char *)malloc((n+1) * sizeof(char));
    scanf("%s", dirs);
    
    // Allocate positions
    int size = n + 1;
    Position *positions = (Position *)malloc(size * sizeof(Position));
    int x = 0, y = 0;
    positions[0].x = x;
    positions[0].y = y;
    positions[0].idx = 0;
    for(int i=1;i<=n;i++){
        char dir = dirs[i-1];
        if(dir == 'N') y +=1;
        else if(dir == 'S') y -=1;
        else if(dir == 'E') x +=1;
        else if(dir == 'W') x -=1;
        positions[i].x = x;
        positions[i].y = y;
        positions[i].idx = i;
    }
    free(dirs);
    
    // Initialize best
    int best_length = 2000000;
    int best_i = -1;
    int best_j = -1;
    char best_dir = 'N';
    
    // Sort by x then y
    qsort(positions, size, sizeof(Position), cmp_x);
    
    // Iterate to find shortcuts with same x
    int start = 0;
    while(start < size){
        int end = start;
        while(end +1 < size && positions[end+1].x == positions[start].x){
            end++;
        }
        for(int i=start; i<end; i++){
            int j = i+1;
            int dy = abs(positions[j].y - positions[i].y);
            if(dy < best_length || (dy == best_length && (positions[i].idx < best_i || (positions[i].idx == best_i && positions[j].idx > best_j)))){
                best_length = dy;
                best_i = positions[i].idx;
                best_j = positions[j].idx;
                best_dir = (positions[j].y > positions[i].y) ? 'N' : 'S';
            }
        }
        start = end +1;
    }
    
    // Sort by y then x
    qsort(positions, size, sizeof(Position), cmp_y);
    
    // Iterate to find shortcuts with same y
    start = 0;
    while(start < size){
        int end = start;
        while(end +1 < size && positions[end+1].y == positions[start].y){
            end++;
        }
        for(int i=start; i<end; i++){
            int j = i+1;
            int dx = abs(positions[j].x - positions[i].x);
            if(dx < best_length || (dx == best_length && (positions[i].idx < best_i || (positions[i].idx == best_i && positions[j].idx > best_j)))){
                best_length = dx;
                best_i = positions[i].idx;
                best_j = positions[j].idx;
                best_dir = (positions[j].x > positions[i].x) ? 'E' : 'W';
            }
        }
        start = end +1;
    }
    
    printf("%d %d %d %c\n", best_length, best_i, best_j, best_dir);
    
    free(positions);
    return 0;
}
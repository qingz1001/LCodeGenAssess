#include <stdio.h>
#include <stdlib.h>

#define MAX_CASTLES 100
#define MAX_BLOCKS 100

int castles[MAX_CASTLES][MAX_BLOCKS];
int heights[MAX_CASTLES];
int n;

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int find_max_height() {
    int max_height = 0;
    int min_height = 10000;
    
    for (int i = 0; i < n; i++) {
        if (heights[i] > max_height) max_height = heights[i];
        if (heights[i] < min_height) min_height = heights[i];
    }
    
    for (int h = max_height; h >= min_height; h--) {
        int possible = 1;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            int j = 0;
            while (sum < h && castles[i][j] != -1) {
                sum += castles[i][j];
                j++;
            }
            if (sum != h) {
                possible = 0;
                break;
            }
        }
        if (possible) return h;
    }
    
    return 0;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        int j = 0;
        int height = 0;
        while (1) {
            scanf("%d", &castles[i][j]);
            if (castles[i][j] == -1) break;
            height += castles[i][j];
            j++;
        }
        heights[i] = height;
        qsort(castles[i], j, sizeof(int), compare);
    }
    
    printf("%d\n", find_max_height());
    
    return 0;
}
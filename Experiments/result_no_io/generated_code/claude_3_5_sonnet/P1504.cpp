#include <stdio.h>
#include <stdlib.h>

#define MAX_CASTLES 100
#define MAX_BLOCKS 100

int castles[MAX_CASTLES][MAX_BLOCKS];
int heights[MAX_CASTLES];
int block_counts[MAX_CASTLES];

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n, i, j, max_height = 0, min_height = 10000;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        int height = 0, count = 0;
        while (1) {
            int block;
            scanf("%d", &block);
            if (block == -1) break;
            castles[i][count++] = block;
            height += block;
        }
        heights[i] = height;
        block_counts[i] = count;
        if (height > max_height) max_height = height;
        if (height < min_height) min_height = height;
    }

    for (int h = max_height; h >= min_height; h--) {
        int possible = 1;
        for (i = 0; i < n; i++) {
            if (heights[i] < h) {
                possible = 0;
                break;
            }
            qsort(castles[i], block_counts[i], sizeof(int), compare);
            int sum = 0, j;
            for (j = 0; j < block_counts[i]; j++) {
                sum += castles[i][j];
                if (sum >= h) break;
            }
            if (sum != h) {
                possible = 0;
                break;
            }
        }
        if (possible) {
            printf("%d\n", h);
            return 0;
        }
    }

    printf("0\n");
    return 0;
}
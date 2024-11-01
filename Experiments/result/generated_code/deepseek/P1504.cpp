#include <stdio.h>
#include <stdlib.h>

#define MAX_CASTLES 100
#define MAX_BLOCKS 100
#define MAX_LENGTH 100

int main() {
    int n;
    scanf("%d", &n);

    int heights[MAX_CASTLES] = {0};
    int max_height = 0;

    for (int i = 0; i < n; i++) {
        int block;
        while (1) {
            scanf("%d", &block);
            if (block == -1) break;
            heights[i] += block;
        }
        if (heights[i] > max_height) {
            max_height = heights[i];
        }
    }

    int min_height = max_height;
    for (int i = 0; i < n; i++) {
        if (heights[i] < min_height) {
            min_height = heights[i];
        }
    }

    printf("%d\n", min_height);

    return 0;
}
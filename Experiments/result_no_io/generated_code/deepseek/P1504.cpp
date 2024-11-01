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

    int possible_heights[MAX_HEIGHT + 1] = {0};
    for (int i = 0; i < n; i++) {
        for (int h = min_height; h >= 0; h--) {
            if (possible_heights[h] == i) {
                possible_heights[h]++;
                if (h + heights[i] <= max_height) {
                    possible_heights[h + heights[i]] = i + 1;
                }
            }
        }
    }

    int result = 0;
    for (int h = max_height; h >= 0; h--) {
        if (possible_heights[h] == n) {
            result = h;
            break;
        }
    }

    printf("%d\n", result);
    return 0;
}
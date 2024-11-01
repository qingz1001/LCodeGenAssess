#include <stdio.h>
#include <stdlib.h>

#define MAX_CASTLES 100
#define MAX_HEIGHT 10000

int main() {
    int n;
    scanf("%d", &n);

    int *castle_heights[MAX_CASTLES];
    int castle_sizes[MAX_CASTLES];
    int total_heights[MAX_HEIGHT] = {0};

    for (int i = 0; i < n; i++) {
        int height = 0;
        int j = 0;
        while (1) {
            int length;
            scanf("%d", &length);
            if (length == -1) break;
            height += length;
            j++;
        }
        castle_heights[i] = (int *)malloc(j * sizeof(int));
        castle_sizes[i] = j;
        for (int k = 0; k < j; k++) {
            scanf("%d", &castle_heights[i][k]);
        }
        total_heights[height]++;
    }

    int max_height = 0;
    for (int i = 0; i < MAX_HEIGHT; i++) {
        if (total_heights[i] == n) {
            max_height = i;
        }
    }

    for (int i = 0; i < n; i++) {
        free(castle_heights[i]);
    }

    printf("%d\n", max_height);

    return 0;
}
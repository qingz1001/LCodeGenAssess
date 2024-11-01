#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_BLOCKS 100
#define MAX_SIDE_LENGTH 100

int main() {
    int n;
    scanf("%d", &n);

    int heights[MAX_N];
    for (int i = 0; i < n; ++i) {
        int sum = 0, block;
        while ((scanf("%d", &block)) && block != -1) {
            sum += block * 6;
        }
        heights[i] = sum;
    }

    // Sort the heights in ascending order
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (heights[i] > heights[j]) {
                int temp = heights[i];
                heights[i] = heights[j];
                heights[j] = temp;
            }
        }
    }

    // Find the maximum possible height
    int max_height = 0;
    for (int i = n - 1; i >= 0; --i) {
        int current_height = heights[i];
        bool can_reach = true;
        for (int j = i - 1; j >= 0; --j) {
            if (current_height <= heights[j]) {
                can_reach = false;
                break;
            }
            current_height -= heights[j];
        }
        if (can_reach) {
            max_height = heights[i];
            break;
        }
    }

    printf("%d\n", max_height);
    return 0;
}
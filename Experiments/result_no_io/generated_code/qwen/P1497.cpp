#include <stdio.h>
#include <stdlib.h>

#define MAXN 21

int n, k, h;
int colors[MAXN];
int grid[MAXN][MAXN];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int start, int end) {
    if (start == end) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 0) {
                    count++;
                }
            }
        }
        if (count == k) {
            printf("Valid layout\n");
        }
    } else {
        for (int i = start; i <= end; i++) {
            swap(&colors[start], &colors[i]);
            permute(start + 1, end);
            swap(&colors[start], &colors[i]);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &h);
    for (int i = 0; i < h; i++) {
        scanf("%d", &colors[i]);
    }

    permute(0, h - 1);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_COORD 20000

typedef struct {
    int height;
    int left;
    int right;
    int index;
} Platform;

int compare_platforms(const void* a, const void* b) {
    Platform* p1 = (Platform*)a;
    Platform* p2 = (Platform*)b;
    return p2->height - p1->height;
}

int find_platform(Platform platforms[], int n, int x, int current_height) {
    for (int i = 0; i < n; i++) {
        if (platforms[i].height < current_height &&
            platforms[i].left < x && platforms[i].right > x) {
            return platforms[i].index;
        }
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    Platform platforms[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
        platforms[i].index = i + 1;
    }

    qsort(platforms, n, sizeof(Platform), compare_platforms);

    for (int i = 0; i < n; i++) {
        int left_land = find_platform(platforms, n, platforms[i].left, platforms[i].height);
        int right_land = find_platform(platforms, n, platforms[i].right, platforms[i].height);
        printf("%d %d\n", left_land, right_land);
    }

    return 0;
}
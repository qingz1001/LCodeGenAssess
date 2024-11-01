#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int height;
    int left;
    int right;
    int index;
} Platform;

int compare(const void *a, const void *b) {
    Platform *p1 = (Platform *)a;
    Platform *p2 = (Platform *)b;
    if (p1->height != p2->height)
        return p2->height - p1->height;
    return p1->index - p2->index;
}

int findPlatform(Platform platforms[], int n, int x, int h) {
    for (int i = 0; i < n; i++) {
        if (platforms[i].left < x && x < platforms[i].right && platforms[i].height < h)
            return platforms[i].index;
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
    
    qsort(platforms, n, sizeof(Platform), compare);
    
    int result[MAX_N][2];
    for (int i = 0; i < n; i++) {
        result[platforms[i].index - 1][0] = findPlatform(platforms, n, platforms[i].left, platforms[i].height);
        result[platforms[i].index - 1][1] = findPlatform(platforms, n, platforms[i].right, platforms[i].height);
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }
    
    return 0;
}
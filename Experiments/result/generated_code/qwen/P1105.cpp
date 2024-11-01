#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int left;
    int right;
    int index;
} Platform;

int compare(const void *a, const void *b) {
    Platform *p1 = (Platform *)a;
    Platform *p2 = (Platform *)b;
    if (p1->height != p2->height) return p2->height - p1->height;
    else return p1->index - p2->index;
}

int findPlatform(int x, Platform platforms[], int n) {
    for (int i = 0; i < n; i++) {
        if (x > platforms[i].left && x < platforms[i].right) return platforms[i].index + 1;
    }
    return 0;
}

int main() {
    int N;
    scanf("%d", &N);
    Platform platforms[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
        platforms[i].index = i;
    }
    qsort(platforms, N, sizeof(Platform), compare);

    for (int i = 0; i < N; i++) {
        int leftIndex = findPlatform(platforms[i].left, platforms, N);
        int rightIndex = findPlatform(platforms[i].right, platforms, N);
        printf("%d %d\n", leftIndex, rightIndex);
    }

    return 0;
}
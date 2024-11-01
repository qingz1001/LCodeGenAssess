#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int left;
    int right;
    int index;
} Platform;

int compare(const void *a, const void *b) {
    return ((Platform *)b)->height - ((Platform *)a)->height;
}

int findPlatform(Platform platforms[], int n, int x, int currentHeight) {
    int targetIndex = -1;
    int minHeight = currentHeight;
    for (int i = 0; i < n; i++) {
        if (platforms[i].height < minHeight && platforms[i].left < x && platforms[i].right > x) {
            if (targetIndex == -1 || platforms[i].height > platforms[targetIndex].height) {
                targetIndex = i;
            }
        }
    }
    return targetIndex == -1 ? 0 : platforms[targetIndex].index;
}

int main() {
    int N;
    scanf("%d", &N);
    Platform platforms[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
        platforms[i].index = i + 1;
    }

    qsort(platforms, N, sizeof(Platform), compare);

    int leftFall[N], rightFall[N];

    for (int i = 0; i < N; i++) {
        leftFall[i] = findPlatform(platforms, N, platforms[i].left, platforms[i].height);
        rightFall[i] = findPlatform(platforms, N, platforms[i].right, platforms[i].height);
    }

    for (int i = 0; i < N; i++) {
        printf("%d %d\n", leftFall[platforms[i].index - 1], rightFall[platforms[i].index - 1]);
    }

    return 0;
}
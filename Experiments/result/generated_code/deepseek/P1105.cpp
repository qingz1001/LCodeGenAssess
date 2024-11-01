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
    return p2->height - p1->height;
}

int findPlatform(Platform platforms[], int n, int x, int height) {
    int minHeight = 200000;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (platforms[i].height < height && platforms[i].left < x && x < platforms[i].right) {
            if (platforms[i].height < minHeight) {
                minHeight = platforms[i].height;
                index = platforms[i].index;
            }
        }
    }
    return index + 1;
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

    int leftFall[N], rightFall[N];

    for (int i = 0; i < N; i++) {
        leftFall[platforms[i].index] = findPlatform(platforms, N, platforms[i].left, platforms[i].height);
        rightFall[platforms[i].index] = findPlatform(platforms, N, platforms[i].right, platforms[i].height);
    }

    for (int i = 0; i < N; i++) {
        printf("%d %d\n", leftFall[i], rightFall[i]);
    }

    return 0;
}
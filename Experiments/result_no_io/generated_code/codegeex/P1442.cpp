#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int height;
    int left;
    int right;
} Platform;

int compare(const void *a, const void *b) {
    Platform *platformA = (Platform *)a;
    Platform *platformB = (Platform *)b;
    return platformA->height - platformB->height;
}

int main() {
    int n, h;
    scanf("%d%d", &n, &h);
    Platform platforms[n];
    int startX, startY;
    scanf("%d%d", &startX, &startY);

    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
    }

    qsort(platforms, n, sizeof(Platform), compare);

    int minTime = -1;
    for (int i = 0; i < n; i++) {
        if (startY > platforms[i].height) {
            continue;
        }
        if (startY < platforms[i].height && startY - platforms[i].height > h) {
            break;
        }

        int timeToReachLeft = abs(startX - platforms[i].left);
        int timeToReachRight = abs(startX - platforms[i].right);

        int timeToFall = platforms[i].height - startY;
        int timeToLeft = timeToFall + timeToReachLeft;
        int timeToRight = timeToFall + timeToReachRight;

        if (minTime == -1 || timeToLeft < minTime) {
            minTime = timeToLeft;
        }
        if (minTime == -1 || timeToRight < minTime) {
            minTime = timeToRight;
        }
    }

    printf("%d\n", minTime);
    return 0;
}
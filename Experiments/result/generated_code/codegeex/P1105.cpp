#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int left;
    int right;
    int index;
} Platform;

int cmp(const void *a, const void *b) {
    Platform *p1 = (Platform *)a;
    Platform *p2 = (Platform *)b;
    if (p1->height != p2->height) {
        return p2->height - p1->height;
    } else {
        return p1->index - p2->index;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    Platform platforms[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
        platforms[i].index = i + 1;
    }

    qsort(platforms, N, sizeof(Platform), cmp);

    for (int i = 0; i < N; i++) {
        int leftFall = 0;
        int rightFall = 0;

        for (int j = 0; j < N; j++) {
            if (platforms[j].height > platforms[i].height) {
                if (platforms[i].left > platforms[j].right) {
                    leftFall = platforms[j].index;
                }
                if (platforms[i].right < platforms[j].left) {
                    rightFall = platforms[j].index;
                }
            }
        }

        printf("%d %d\n", leftFall, rightFall);
    }

    return 0;
}
#include <stdio.h>

typedef struct {
    int height;
    int left;
    int right;
    int index;
} Platform;

int compare(const void *a, const void *b) {
    Platform *platformA = (Platform *)a;
    Platform *platformB = (Platform *)b;
    if (platformA->height == platformB->height) {
        return platformA->index - platformB->index;
    }
    return platformA->height - platformB->height;
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

    for (int i = 0; i < N; i++) {
        int leftFall = 0;
        int rightFall = 0;
        for (int j = 0; j < N; j++) {
            if (platforms[j].height > platforms[i].height && platforms[i].left < platforms[j].right && platforms[j].left < platforms[i].right) {
                leftFall = platforms[j].index;
                break;
            }
        }
        for (int j = 0; j < N; j++) {
            if (platforms[j].height > platforms[i].height && platforms[i].right > platforms[j].left && platforms[j].left < platforms[i].right) {
                rightFall = platforms[j].index;
                break;
            }
        }
        printf("%d %d\n", leftFall, rightFall);
    }

    return 0;
}
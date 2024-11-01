#include <stdio.h>
#include <stdlib.h>

#define MAX_PLATFORMS 1000
#define MAX_COORDINATE 20000

typedef struct {
    int height;
    int left;
    int right;
    int index;
} Platform;

int compare(const void *a, const void *b) {
    Platform *p1 = (Platform *)a;
    Platform *p2 = (Platform *)b;
    if (p1->height != p2->height) {
        return p2->height - p1->height; // Descending order of height
    } else {
        return p1->index - p2->index; // Ascending order of index
    }
}

void find_platforms(Platform platforms[], int n) {
    for (int i = 0; i < n; i++) {
        int left_index = 0;
        int right_index = 0;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            if (platforms[j].left < platforms[i].right && platforms[j].right > platforms[i].left) {
                if (platforms[j].height < platforms[i].height) {
                    if (platforms[j].left >= platforms[i].left) {
                        left_index = j + 1;
                    }
                    if (platforms[j].right <= platforms[i].right) {
                        right_index = j + 1;
                    }
                }
            }
        }
        printf("%d %d\n", left_index, right_index);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Platform platforms[MAX_PLATFORMS];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
        platforms[i].index = i + 1;
    }

    qsort(platforms, n, sizeof(Platform), compare);

    find_platforms(platforms, n);

    return 0;
}
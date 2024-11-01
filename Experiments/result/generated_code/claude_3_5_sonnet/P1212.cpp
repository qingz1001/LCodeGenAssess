#include <stdio.h>
#include <stdlib.h>

#define MAX_SOLUTIONS 100

typedef struct {
    int width;
    int height;
} Rectangle;

typedef struct {
    int width;
    int height;
} Solution;

int compare(const void *a, const void *b) {
    Solution *s1 = (Solution *)a;
    Solution *s2 = (Solution *)b;
    if (s1->width != s2->width)
        return s1->width - s2->width;
    return s1->height - s2->height;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int tryPlacement(Rectangle rects[], int w, int h) {
    int used[4] = {0};
    int x[4] = {0};
    int y[4] = {0};

    for (int i = 0; i < 4; i++) {
        int placed = 0;
        for (int j = 0; j < 4; j++) {
            if (!used[j]) {
                int fit = 1;
                for (int k = 0; k < i; k++) {
                    if (x[k] < x[j] + rects[j].width && x[j] < x[k] + rects[k].width &&
                        y[k] < y[j] + rects[j].height && y[j] < y[k] + rects[k].height) {
                        fit = 0;
                        break;
                    }
                }
                if (fit && x[j] + rects[j].width <= w && y[j] + rects[j].height <= h) {
                    used[j] = 1;
                    placed = 1;
                    break;
                }
            }
        }
        if (!placed) return 0;
    }
    return 1;
}

int main() {
    Rectangle rects[4];
    Solution solutions[MAX_SOLUTIONS];
    int solutionCount = 0;
    int minArea = 1000000;

    for (int i = 0; i < 4; i++) {
        scanf("%d %d", &rects[i].width, &rects[i].height);
    }

    for (int w = 1; w <= 50; w++) {
        for (int h = w; h <= 50; h++) {
            if (tryPlacement(rects, w, h)) {
                int area = w * h;
                if (area < minArea) {
                    minArea = area;
                    solutionCount = 0;
                }
                if (area == minArea) {
                    solutions[solutionCount].width = w;
                    solutions[solutionCount].height = h;
                    solutionCount++;
                }
            }
        }
    }

    qsort(solutions, solutionCount, sizeof(Solution), compare);

    printf("%d\n", minArea);
    for (int i = 0; i < solutionCount; i++) {
        if (i == 0 || solutions[i].width != solutions[i-1].width || solutions[i].height != solutions[i-1].height) {
            printf("%d %d\n", solutions[i].width, solutions[i].height);
        }
    }

    return 0;
}
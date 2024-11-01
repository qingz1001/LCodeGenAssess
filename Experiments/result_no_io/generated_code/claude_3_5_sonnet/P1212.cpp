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
    int area;
} Solution;

int compare(const void* a, const void* b) {
    Solution* s1 = (Solution*)a;
    Solution* s2 = (Solution*)b;
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

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rotate(Rectangle* rect) {
    swap(&rect->width, &rect->height);
}

int pack(Rectangle rects[], int n, Solution solutions[]) {
    int count = 0;
    int minArea = 1e9;

    for (int r1 = 0; r1 < 2; r1++) {
        for (int r2 = 0; r2 < 2; r2++) {
            for (int r3 = 0; r3 < 2; r3++) {
                for (int r4 = 0; r4 < 2; r4++) {
                    int w1 = rects[0].width + rects[1].width;
                    int h1 = max(rects[0].height, rects[1].height);
                    int w2 = rects[2].width + rects[3].width;
                    int h2 = max(rects[2].height, rects[3].height);

                    int w = max(w1, w2);
                    int h = h1 + h2;

                    int area = w * h;
                    if (area <= minArea) {
                        if (area < minArea) {
                            count = 0;
                            minArea = area;
                        }
                        solutions[count].width = min(w, h);
                        solutions[count].height = max(w, h);
                        solutions[count].area = area;
                        count++;
                    }

                    rotate(&rects[3]);
                }
                rotate(&rects[2]);
            }
            rotate(&rects[1]);
        }
        rotate(&rects[0]);
    }

    qsort(solutions, count, sizeof(Solution), compare);

    int uniqueCount = 1;
    for (int i = 1; i < count; i++) {
        if (solutions[i].width != solutions[i-1].width || solutions[i].height != solutions[i-1].height) {
            solutions[uniqueCount] = solutions[i];
            uniqueCount++;
        }
    }

    return uniqueCount;
}

int main() {
    Rectangle rects[4];
    Solution solutions[MAX_SOLUTIONS];

    for (int i = 0; i < 4; i++) {
        scanf("%d %d", &rects[i].width, &rects[i].height);
    }

    int solutionCount = pack(rects, 4, solutions);

    printf("%d\n", solutions[0].area);
    for (int i = 0; i < solutionCount; i++) {
        printf("%d %d\n", solutions[i].width, solutions[i].height);
    }

    return 0;
}
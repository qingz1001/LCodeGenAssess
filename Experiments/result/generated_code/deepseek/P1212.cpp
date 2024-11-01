#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int width;
    int height;
} Rectangle;

typedef struct {
    int width;
    int height;
} Solution;

int compare(const void *a, const void *b) {
    Solution *solA = (Solution *)a;
    Solution *solB = (Solution *)b;
    if (solA->width != solB->width) {
        return solA->width - solB->width;
    }
    return solA->height - solB->height;
}

void addSolution(Solution *solutions, int *solutionCount, int width, int height) {
    if (width > height) {
        int temp = width;
        width = height;
        height = temp;
    }
    for (int i = 0; i < *solutionCount; i++) {
        if (solutions[i].width == width && solutions[i].height == height) {
            return;
        }
    }
    solutions[*solutionCount].width = width;
    solutions[*solutionCount].height = height;
    (*solutionCount)++;
}

int main() {
    Rectangle rects[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d %d", &rects[i].width, &rects[i].height);
    }

    Solution solutions[100];
    int solutionCount = 0;
    int minArea = 1000000;

    // Case 1: All rectangles in one row
    int width1 = rects[0].width + rects[1].width + rects[2].width + rects[3].width;
    int height1 = 0;
    for (int i = 0; i < 4; i++) {
        if (rects[i].height > height1) {
            height1 = rects[i].height;
        }
    }
    if (width1 * height1 < minArea) {
        minArea = width1 * height1;
        solutionCount = 0;
        addSolution(solutions, &solutionCount, width1, height1);
    } else if (width1 * height1 == minArea) {
        addSolution(solutions, &solutionCount, width1, height1);
    }

    // Case 2: Two rows, two rectangles each
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int width2 = rects[i].width + rects[j].width;
            int height2 = rects[i].height + rects[j].height;
            if (width2 * height2 < minArea) {
                minArea = width2 * height2;
                solutionCount = 0;
                addSolution(solutions, &solutionCount, width2, height2);
            } else if (width2 * height2 == minArea) {
                addSolution(solutions, &solutionCount, width2, height2);
            }
        }
    }

    // Case 3: Three rectangles in one row, one in another
    for (int i = 0; i < 4; i++) {
        int width3 = rects[i].width;
        int height3 = 0;
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                width3 += rects[j].width;
                if (rects[j].height > height3) {
                    height3 = rects[j].height;
                }
            }
        }
        height3 += rects[i].height;
        if (width3 * height3 < minArea) {
            minArea = width3 * height3;
            solutionCount = 0;
            addSolution(solutions, &solutionCount, width3, height3);
        } else if (width3 * height3 == minArea) {
            addSolution(solutions, &solutionCount, width3, height3);
        }
    }

    // Case 4: Two rectangles in one row, two in another
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int width4 = rects[i].width + rects[j].width;
            int height4 = rects[i].height + rects[j].height;
            if (width4 * height4 < minArea) {
                minArea = width4 * height4;
                solutionCount = 0;
                addSolution(solutions, &solutionCount, width4, height4);
            } else if (width4 * height4 == minArea) {
                addSolution(solutions, &solutionCount, width4, height4);
            }
        }
    }

    // Case 5: Two rectangles in one row, two in another
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int width5 = rects[i].width + rects[j].width;
            int height5 = rects[i].height + rects[j].height;
            if (width5 * height5 < minArea) {
                minArea = width5 * height5;
                solutionCount = 0;
                addSolution(solutions, &solutionCount, width5, height5);
            } else if (width5 * height5 == minArea) {
                addSolution(solutions, &solutionCount, width5, height5);
            }
        }
    }

    // Case 6: Two rectangles in one row, two in another
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int width6 = rects[i].width + rects[j].width;
            int height6 = rects[i].height + rects[j].height;
            if (width6 * height6 < minArea) {
                minArea = width6 * height6;
                solutionCount = 0;
                addSolution(solutions, &solutionCount, width6, height6);
            } else if (width6 * height6 == minArea) {
                addSolution(solutions, &solutionCount, width6, height6);
            }
        }
    }

    qsort(solutions, solutionCount, sizeof(Solution), compare);

    printf("%d\n", minArea);
    for (int i = 0; i < solutionCount; i++) {
        printf("%d %d\n", solutions[i].width, solutions[i].height);
    }

    return 0;
}
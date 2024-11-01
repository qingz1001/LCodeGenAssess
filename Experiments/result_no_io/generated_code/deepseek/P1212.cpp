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
} EnclosingRectangle;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void addSolution(EnclosingRectangle *solutions, int *solutionCount, int width, int height) {
    for (int i = 0; i < *solutionCount; i++) {
        if (solutions[i].width == width && solutions[i].height == height) {
            return;
        }
    }
    solutions[*solutionCount].width = width;
    solutions[*solutionCount].height = height;
    (*solutionCount)++;
}

void sortSolutions(EnclosingRectangle *solutions, int solutionCount) {
    for (int i = 0; i < solutionCount; i++) {
        if (solutions[i].width > solutions[i].height) {
            int temp = solutions[i].width;
            solutions[i].width = solutions[i].height;
            solutions[i].height = temp;
        }
    }
    qsort(solutions, solutionCount, sizeof(EnclosingRectangle), compare);
}

int main() {
    Rectangle rects[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d %d", &rects[i].width, &rects[i].height);
    }

    EnclosingRectangle solutions[100];
    int solutionCount = 0;
    int minArea = 1000000;

    // Case 1: All rectangles in one row
    int width = rects[0].width + rects[1].width + rects[2].width + rects[3].width;
    int height = 0;
    for (int i = 0; i < 4; i++) {
        if (rects[i].height > height) {
            height = rects[i].height;
        }
    }
    if (width * height < minArea) {
        minArea = width * height;
        solutionCount = 0;
        addSolution(solutions, &solutionCount, width, height);
    } else if (width * height == minArea) {
        addSolution(solutions, &solutionCount, width, height);
    }

    // Case 2: Two rows, two rectangles in each row
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            for (int k = 0; k < 4; k++) {
                if (k == i || k == j) continue;
                for (int l = 0; l < 4; l++) {
                    if (l == i || l == j || l == k) continue;
                    int width1 = rects[i].width + rects[j].width;
                    int height1 = rects[i].height > rects[j].height ? rects[i].height : rects[j].height;
                    int width2 = rects[k].width + rects[l].width;
                    int height2 = rects[k].height > rects[l].height ? rects[k].height : rects[l].height;
                    int totalWidth = width1 > width2 ? width1 : width2;
                    int totalHeight = height1 + height2;
                    if (totalWidth * totalHeight < minArea) {
                        minArea = totalWidth * totalHeight;
                        solutionCount = 0;
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    } else if (totalWidth * totalHeight == minArea) {
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    }
                }
            }
        }
    }

    // Case 3: Three rectangles in one row, one in another row
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            for (int k = 0; k < 4; k++) {
                if (k == i || k == j) continue;
                for (int l = 0; l < 4; l++) {
                    if (l == i || l == j || l == k) continue;
                    int width1 = rects[i].width + rects[j].width + rects[k].width;
                    int height1 = rects[i].height > rects[j].height ? rects[i].height : rects[j].height;
                    height1 = height1 > rects[k].height ? height1 : rects[k].height;
                    int totalWidth = width1 > rects[l].width ? width1 : rects[l].width;
                    int totalHeight = height1 + rects[l].height;
                    if (totalWidth * totalHeight < minArea) {
                        minArea = totalWidth * totalHeight;
                        solutionCount = 0;
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    } else if (totalWidth * totalHeight == minArea) {
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    }
                }
            }
        }
    }

    // Case 4: Two rectangles in one row, two in another row, but one rectangle is rotated
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            for (int k = 0; k < 4; k++) {
                if (k == i || k == j) continue;
                for (int l = 0; l < 4; l++) {
                    if (l == i || l == j || l == k) continue;
                    int width1 = rects[i].width + rects[j].width;
                    int height1 = rects[i].height > rects[j].height ? rects[i].height : rects[j].height;
                    int width2 = rects[k].width + rects[l].height;
                    int height2 = rects[k].height > rects[l].width ? rects[k].height : rects[l].width;
                    int totalWidth = width1 > width2 ? width1 : width2;
                    int totalHeight = height1 + height2;
                    if (totalWidth * totalHeight < minArea) {
                        minArea = totalWidth * totalHeight;
                        solutionCount = 0;
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    } else if (totalWidth * totalHeight == minArea) {
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    }
                }
            }
        }
    }

    // Case 5: Two rectangles in one row, two in another row, but both rectangles are rotated
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            for (int k = 0; k < 4; k++) {
                if (k == i || k == j) continue;
                for (int l = 0; l < 4; l++) {
                    if (l == i || l == j || l == k) continue;
                    int width1 = rects[i].width + rects[j].height;
                    int height1 = rects[i].height > rects[j].width ? rects[i].height : rects[j].width;
                    int width2 = rects[k].width + rects[l].height;
                    int height2 = rects[k].height > rects[l].width ? rects[k].height : rects[l].width;
                    int totalWidth = width1 > width2 ? width1 : width2;
                    int totalHeight = height1 + height2;
                    if (totalWidth * totalHeight < minArea) {
                        minArea = totalWidth * totalHeight;
                        solutionCount = 0;
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    } else if (totalWidth * totalHeight == minArea) {
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    }
                }
            }
        }
    }

    // Case 6: One rectangle in one row, three in another row, but one rectangle is rotated
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            for (int k = 0; k < 4; k++) {
                if (k == i || k == j) continue;
                for (int l = 0; l < 4; l++) {
                    if (l == i || l == j || l == k) continue;
                    int width1 = rects[i].width + rects[j].width + rects[k].height;
                    int height1 = rects[i].height > rects[j].height ? rects[i].height : rects[j].height;
                    height1 = height1 > rects[k].width ? height1 : rects[k].width;
                    int totalWidth = width1 > rects[l].width ? width1 : rects[l].width;
                    int totalHeight = height1 + rects[l].height;
                    if (totalWidth * totalHeight < minArea) {
                        minArea = totalWidth * totalHeight;
                        solutionCount = 0;
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    } else if (totalWidth * totalHeight == minArea) {
                        addSolution(solutions, &solutionCount, totalWidth, totalHeight);
                    }
                }
            }
        }
    }

    sortSolutions(solutions, solutionCount);

    printf("%d\n", minArea);
    for (int i = 0; i < solutionCount; i++) {
        printf("%d %d\n", solutions[i].width, solutions[i].height);
    }

    return 0;
}
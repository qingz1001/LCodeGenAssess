#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

int rectangles[4][2];
int minArea = INT_MAX;
int solutions[MAX_SIZE * MAX_SIZE];

void rotate(int x, int y) {
    return y == 0 ? x : rotate(y, x % y);
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void findMinRectangle(int index, int width, int height) {
    if (index == 4) {
        int area = width * height;
        if (area < minArea) {
            minArea = area;
            for (int i = 0; i < minArea; i++) {
                solutions[i] = 0;
            }
            for (int i = 0; i < 4; i++) {
                solutions[rectangles[i][0]]++;
                solutions[rectangles[i][1]]++;
            }
        } else if (area == minArea) {
            for (int i = 0; i < 4; i++) {
                solutions[rectangles[i][0]]++;
                solutions[rectangles[i][1]]++;
            }
        }
        return;
    }

    int w = rectangles[index][0];
    int h = rectangles[index][1];
    if (w > h) {
        int temp = w;
        w = h;
        h = temp;
    }

    findMinRectangle(index + 1, width + w, height);
    findMinRectangle(index + 1, width, height + h);
}

int main() {
    for (int i = 0; i < 4; i++) {
        scanf("%d %d", &rectangles[i][0], &rectangles[i][1]);
    }

    findMinRectangle(0, 0, 0);

    printf("%d\n", minArea);
    for (int i = 1; i <= max(solutions); i++) {
        if (solutions[i] > 0) {
            printf("%d %d\n", i / gcd(i, solutions[i]), solutions[i]);
        }
    }

    return 0;
}
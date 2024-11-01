#include <stdio.h>
#include <stdlib.h>

#define MAX_N 4
#define MAX_SIZE 50

int rectangles[MAX_N][2];
int min_area = INT_MAX;
int solutions[MAX_N * MAX_N][2];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rotate(int *width, int *height) {
    swap(width, height);
}

void mirror_horizontal(int *width, int *height) {
    *width = -(*width);
}

void mirror_vertical(int *width, int *height) {
    *height = -(*height);
}

void try_place(int x, int y, int width, int height, int count) {
    if (x + width > min_area || y + height > min_area) return;

    int placed = 0;
    for (int i = 0; i < count; i++) {
        int rx = x + rectangles[i][0];
        int ry = y + rectangles[i][1];
        if (rx >= x && rx <= x + width && ry >= y && ry <= y + height) {
            placed = 1;
            break;
        }
    }

    if (!placed) {
        int area = width * height;
        if (area < min_area) {
            min_area = area;
            int sol_count = 0;
            for (int i = 0; i < count; i++) {
                int rx = x + rectangles[i][0];
                int ry = y + rectangles[i][1];
                if (rx == x && ry == y) {
                    solutions[sol_count][0] = width;
                    solutions[sol_count][1] = height;
                    sol_count++;
                } else if (rx == x + width && ry == y) {
                    solutions[sol_count][0] = height;
                    solutions[sol_count][1] = width;
                    sol_count++;
                }
            }
        }
    }
}

void place_rectangles(int index, int width, int height) {
    if (index == MAX_N) {
        try_place(0, 0, width, height, MAX_N);
        return;
    }

    int rect_width = rectangles[index][0];
    int rect_height = rectangles[index][1];

    place_rectangles(index + 1, width + rect_width, height);
    place_rectangles(index + 1, width, height + rect_height);

    rotate(&rect_width, &rect_height);
    place_rectangles(index + 1, width + rect_width, height);
    place_rectangles(index + 1, width, height + rect_height);

    mirror_horizontal(&rect_width, &rect_height);
    place_rectangles(index + 1, width + rect_width, height);
    place_rectangles(index + 1, width, height + rect_height);

    mirror_vertical(&rect_width, &rect_height);
    place_rectangles(index + 1, width + rect_width, height);
    place_rectangles(index + 1, width, height + rect_height);
}

int main() {
    for (int i = 0; i < MAX_N; i++) {
        scanf("%d %d", &rectangles[i][0], &rectangles[i][1]);
    }

    place_rectangles(0, 0, 0);

    printf("%d\n", min_area);
    for (int i = 0; i < MAX_N * MAX_N; i++) {
        if (solutions[i][0] != 0) {
            printf("%d %d\n", solutions[i][0], solutions[i][1]);
        }
    }

    return 0;
}
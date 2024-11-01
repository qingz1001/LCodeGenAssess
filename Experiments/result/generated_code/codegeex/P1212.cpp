#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int rectangles[4][2];
int min_area = MAX * MAX;
int solutions[MAX * MAX];
int num_solutions = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rotate(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int area(int a, int b) {
    return a * b;
}

void place_rectangles(int x, int y, int *used, int *max_x, int *max_y) {
    for (int i = 0; i < 4; i++) {
        if (used[i]) continue;
        used[i] = 1;
        int new_x = x + rectangles[i][0];
        int new_y = y + rectangles[i][1];
        if (new_x > *max_x) *max_x = new_x;
        if (new_y > *max_y) *max_y = new_y;
        if (area(*max_x, *max_y) < min_area) {
            min_area = area(*max_x, *max_y);
            num_solutions = 0;
            solutions[num_solutions++] = min_area;
        } else if (area(*max_x, *max_y) == min_area) {
            solutions[num_solutions++] = min_area;
        }
        place_rectangles(new_x, y, used, max_x, max_y);
        place_rectangles(x, new_y, used, max_x, max_y);
        used[i] = 0;
    }
}

void solve() {
    int used[4] = {0};
    int max_x = 0, max_y = 0;
    place_rectangles(0, 0, used, &max_x, &max_y);
}

int main() {
    for (int i = 0; i < 4; i++) {
        scanf("%d%d", &rectangles[i][0], &rectangles[i][1]);
    }
    solve();
    printf("%d\n", min_area);
    for (int i = 0; i < num_solutions; i++) {
        int p = solutions[i] / 50;
        int q = solutions[i] % 50;
        if (p < q) {
            printf("%d %d\n", p, q);
        } else {
            printf("%d %d\n", q, p);
        }
    }
    return 0;
}
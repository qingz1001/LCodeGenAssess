#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 300005

typedef struct {
    int x, y, r;
} Circle;

int n;
Circle circles[MAXN];
int deleted_by[MAXN];

// Function to calculate the distance between two points
double dist(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Function to check if two circles intersect
int intersects(Circle c1, Circle c2) {
    double d = dist(c1.x, c1.y, c2.x, c2.y);
    return d <= c1.r + c2.r;
}

void process() {
    for (int i = 0; i < n; ++i) {
        int max_radius_index = i;
        double max_radius = circles[i].r;
        for (int j = i + 1; j < n; ++j) {
            if (circles[j].r > max_radius || (circles[j].r == max_radius && j < max_radius_index)) {
                max_radius = circles[j].r;
                max_radius_index = j;
            }
        }

        // Delete the circle with the maximum radius and all intersecting circles
        deleted_by[max_radius_index] = -1;
        for (int j = 0; j < n; ++j) {
            if (intersects(circles[max_radius_index], circles[j]) && j != max_radius_index) {
                deleted_by[j] = max_radius_index;
            }
        }

        // Move the last circle to the current position and reduce the size of the array
        circles[max_radius_index] = circles[--n];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &circles[i].x, &circles[i].y, &circles[i].r);
    }

    process();

    for (int i = 0; i < n; ++i) {
        printf("%d ", deleted_by[i]);
    }
    printf("\n");

    return 0;
}
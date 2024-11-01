#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

int N;
Point rect_min, rect_max;
Point points[6];
double max_sum = 0.0;
double pi = 3.14159265358979323846;

// Function to compute distance between two points
double distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Recursive function to generate all permutations and compute maximum sum
void backtrack(int depth, int used[], int perm[], Point placed_points[], double radii[], double current_sum, double *max_sum_ptr) {
    if (depth == N) {
        if (current_sum > *max_sum_ptr) {
            *max_sum_ptr = current_sum;
        }
        return;
    }
    for(int i = 0; i < N; i++) {
        if(!used[i]) {
            used[i] = 1;
            perm[depth] = i;
            // Compute radius for this point
            Point p = points[i];
            double min_dist = fmin(fmin(p.x - rect_min.x, rect_max.x - p.x), fmin(p.y - rect_min.y, rect_max.y - p.y));
            for(int j = 0; j < depth; j++) {
                double d = distance(p, placed_points[j]) - radii[j];
                if(d < min_dist) {
                    min_dist = d;
                }
            }
            if(min_dist < 0) min_dist = 0.0;
            radii[depth] = min_dist;
            placed_points[depth] = p;
            double new_sum = current_sum + pi * min_dist * min_dist;
            backtrack(depth + 1, used, perm, placed_points, radii, new_sum, max_sum_ptr);
            used[i] = 0;
        }
    }
}

int main(){
    scanf("%d", &N);
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    // Determine rectangle boundaries
    rect_min.x = (x1 < x2) ? x1 : x2;
    rect_max.x = (x1 > x2) ? x1 : x2;
    rect_min.y = (y1 < y2) ? y1 : y2;
    rect_max.y = (y1 > y2) ? y1 : y2;
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &x1, &y1);
        points[i].x = (double)x1;
        points[i].y = (double)y1;
    }
    double width = rect_max.x - rect_min.x;
    double height = rect_max.y - rect_min.y;
    double rect_area = width * height;
    int used[6] = {0};
    int perm[6];
    Point placed_points[6];
    double radii[6];
    backtrack(0, used, perm, placed_points, radii, 0.0, &max_sum);
    double residual = rect_area - max_sum;
    // Round to nearest integer
    long long result = llround(residual);
    printf("%lld\n", result);
    return 0;
}
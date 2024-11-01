#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long x;
    long long y;
} Point;

int cmp_x(const void* a, const void* b) {
    Point* pa = (Point*)a;
    Point* pb = (Point*)b;
    if (pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    if (pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    return 0;
}

int cmp_y(const void* a, const void* b) {
    Point* pa = *(Point**)a;
    Point* pb = *(Point**)b;
    if (pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    if (pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    return 0;
}

double closest_pair(Point* points, int left, int right, Point** sorted_y) {
    if (right - left <= 3) {
        double min_dist = 1e20;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                double dist = sqrt((double)(points[i].x - points[j].x) * (points[i].x - points[j].x) +
                                   (double)(points[i].y - points[j].y) * (points[i].y - points[j].y));
                if (dist < min_dist)
                    min_dist = dist;
            }
        }
        // Sort sorted_y
        qsort(sorted_y + left, right - left, sizeof(Point*), cmp_y);
        return min_dist;
    }

    int mid = left + (right - left) / 2;
    double mid_x = points[mid].x;
    double dl = closest_pair(points, left, mid, sorted_y);
    double dr = closest_pair(points, mid, right, sorted_y);
    double d = (dl < dr) ? dl : dr;

    // Merge sorted_y
    int i = left, j = mid;
    Point** temp = (Point**)malloc((right - left) * sizeof(Point*));
    int k = 0;
    while (i < mid && j < right) {
        if (sorted_y[i]->y < sorted_y[j]->y) {
            temp[k++] = sorted_y[i++];
        }
        else {
            temp[k++] = sorted_y[j++];
        }
    }
    while (i < mid)
        temp[k++] = sorted_y[i++];
    while (j < right)
        temp[k++] = sorted_y[j++];
    for (i = left; i < right; ++i)
        sorted_y[i] = temp[i - left];
    free(temp);

    // Create strip
    Point** strip = (Point**)malloc((right - left) * sizeof(Point*));
    int strip_size = 0;
    for (i = left; i < right; ++i) {
        if (fabs((double)(sorted_y[i]->x - mid_x)) < d)
            strip[strip_size++] = sorted_y[i];
    }

    for (i = 0; i < strip_size; ++i) {
        for (int j = i + 1; j < strip_size && (strip[j]->y - strip[i]->y) < d; ++j) {
            double dist = sqrt((double)(strip[i]->x - strip[j]->x) * (strip[i]->x - strip[j]->x) +
                               (double)(strip[i]->y - strip[j]->y) * (strip[i]->y - strip[j]->y));
            if (dist < d)
                d = dist;
        }
    }
    free(strip);
    return d;
}

int main(){
    int n;
    scanf("%d", &n);
    Point* points = (Point*)malloc(n * sizeof(Point));
    for(int i=0;i<n;i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }
    qsort(points, n, sizeof(Point), cmp_x);
    Point** sorted_y = (Point**)malloc(n * sizeof(Point*));
    for(int i=0;i<n;i++) sorted_y[i] = &points[i];
    double min_dist = closest_pair(points, 0, n, sorted_y);
    printf("%.4lf\n", min_dist);
    free(points);
    free(sorted_y);
    return 0;
}
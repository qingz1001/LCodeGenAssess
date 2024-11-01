#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

// Comparator for sorting points by x, then by y
int cmp_point(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->x != pb->x)
        return pa->x - pb->x;
    return pa->y - pb->y;
}

// Comparator for sorting y's
int cmp_int(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

// Function to check if there exists a square of size s containing at least C clovers
int check(int s, Point *points, int N, int C) {
    for(int i = 0; i < N; i++) {
        int x_start = points[i].x;
        int x_end = x_start + s;
        int j = i;
        // Find the first point with x > x_end
        while(j < N && points[j].x <= x_end)
            j++;
        int count = j - i;
        if(count < C)
            continue;
        // Collect y's
        int y_list[500];
        for(int k = i; k < j; k++) {
            y_list[k - i] = points[k].y;
        }
        // Sort y's
        qsort(y_list, count, sizeof(int), cmp_int);
        // Sliding window on y's
        int l = 0;
        for(int r = 0; r < count; r++) {
            while(y_list[r] > y_list[l] + s)
                l++;
            if(r - l + 1 >= C)
                return 1;
        }
    }
    return 0;
}

int main(){
    int C, N;
    scanf("%d %d", &C, &N);
    Point points[500];
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    qsort(points, N, sizeof(Point), cmp_point);
    int left = 0, right = 10000;
    while(left < right){
        int mid = left + (right - left) / 2;
        if(check(mid, points, N, C))
            right = mid;
        else
            left = mid + 1;
    }
    printf("%d\n", left);
    return 0;
}
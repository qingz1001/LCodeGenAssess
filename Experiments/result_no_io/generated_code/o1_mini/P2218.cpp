#include <stdio.h>
#include <stdlib.h>

// Structure to hold points
typedef struct {
    long long x, y;
} Point;

// Comparator for sorting points by x, then y
int cmp_points(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    if (pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    return 0;
}

// Function to check if points from start to end can be covered by one square of size L
int can_cover_one_square(Point *points, int start, int end, long long L) {
    long long min_y = points[start].y;
    long long max_y = points[start].y;
    for(int i = start; i <= end; i++) {
        if(points[i].y < min_y) min_y = points[i].y;
        if(points[i].y > max_y) max_y = points[i].y;
    }
    return (points[end].x - points[start].x <= L) && (max_y - min_y <= L);
}

// Recursive function to check if points can be covered with k squares
int cover(Point *points, int N, int start, int k, long long L) {
    if(k == 0) return start > N - 1;
    if(start > N - 1) return 1;
    for(int end = start; end < N; end++) {
        if(can_cover_one_square(points, start, end, L)) {
            if(cover(points, N, end + 1, k - 1, L))
                return 1;
        }
        else {
            break;
        }
    }
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    Point *points = (Point*)malloc(sizeof(Point) * N);
    for(int i = 0; i < N; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }
    qsort(points, N, sizeof(Point), cmp_points);
    long long left = 0, right = 2000000000, answer = -1;
    while(left <= right){
        long long mid = left + (right - left) / 2;
        if(cover(points, N, 0, 3, mid)){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld\n", answer);
    free(points);
    return 0;
}
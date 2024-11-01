#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    long long x;
    long long y;
    long long min_dist;
} Point;

int N;
Point *points;

// Sorted array indexes
int *sorted1;
int *sorted2;
int *sorted3;
int *sorted4;

// Comparator for sorted1: t1 = x + y
int cmp1(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    long long ta = points[ia].x + points[ia].y;
    long long tb = points[ib].x + points[ib].y;
    if (ta != tb) return (ta < tb) ? -1 : 1;
    if (points[ia].x != points[ib].x) return (points[ia].x < points[ib].x) ? -1 : 1;
    if (points[ia].y != points[ib].y) return (points[ia].y < points[ib].y) ? -1 : 1;
    return 0;
}

// Comparator for sorted2: t2 = x - y
int cmp2(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    long long ta = points[ia].x - points[ia].y;
    long long tb = points[ib].x - points[ib].y;
    if (ta != tb) return (ta < tb) ? -1 : 1;
    if (points[ia].x != points[ib].x) return (points[ia].x < points[ib].x) ? -1 : 1;
    if (points[ia].y != points[ib].y) return (points[ia].y < points[ib].y) ? -1 : 1;
    return 0;
}

// Comparator for sorted3: t3 = -x + y
int cmp3(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    long long ta = -points[ia].x + points[ia].y;
    long long tb = -points[ib].x + points[ib].y;
    if (ta != tb) return (ta < tb) ? -1 : 1;
    if (points[ia].x != points[ib].x) return (points[ia].x < points[ib].x) ? -1 : 1;
    if (points[ia].y != points[ib].y) return (points[ia].y < points[ib].y) ? -1 : 1;
    return 0;
}

// Comparator for sorted4: t4 = -x - y
int cmp4(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    long long ta = -points[ia].x - points[ia].y;
    long long tb = -points[ib].x - points[ib].y;
    if (ta != tb) return (ta < tb) ? -1 : 1;
    if (points[ia].x != points[ib].x) return (points[ia].x < points[ib].x) ? -1 : 1;
    if (points[ia].y != points[ib].y) return (points[ia].y < points[ib].y) ? -1 : 1;
    return 0;
}

long long manhattan_dist(int a, int b){
    return abs(points[a].x - points[b].x) + abs(points[a].y - points[b].y);
}

int main(){
    scanf("%d", &N);
    points = (Point*)malloc(N * sizeof(Point));
    for(int i=0;i<N;i++){
        scanf("%lld %lld", &points[i].x, &points[i].y);
        points[i].min_dist = 1e18;
    }

    // Allocate sorted arrays
    sorted1 = (int*)malloc(N * sizeof(int));
    sorted2 = (int*)malloc(N * sizeof(int));
    sorted3 = (int*)malloc(N * sizeof(int));
    sorted4 = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++){
        sorted1[i] = i;
        sorted2[i] = i;
        sorted3[i] = i;
        sorted4[i] = i;
    }

    // Sort and update min_dist
    qsort(sorted1, N, sizeof(int), cmp1);
    for(int i=0;i<N;i++){
        int current = sorted1[i];
        if(i > 0){
            int prev = sorted1[i-1];
            long long dist = manhattan_dist(current, prev);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
        if(i < N-1){
            int next = sorted1[i+1];
            long long dist = manhattan_dist(current, next);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
    }

    qsort(sorted2, N, sizeof(int), cmp2);
    for(int i=0;i<N;i++){
        int current = sorted2[i];
        if(i > 0){
            int prev = sorted2[i-1];
            long long dist = manhattan_dist(current, prev);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
        if(i < N-1){
            int next = sorted2[i+1];
            long long dist = manhattan_dist(current, next);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
    }

    qsort(sorted3, N, sizeof(int), cmp3);
    for(int i=0;i<N;i++){
        int current = sorted3[i];
        if(i > 0){
            int prev = sorted3[i-1];
            long long dist = manhattan_dist(current, prev);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
        if(i < N-1){
            int next = sorted3[i+1];
            long long dist = manhattan_dist(current, next);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
    }

    qsort(sorted4, N, sizeof(int), cmp4);
    for(int i=0;i<N;i++){
        int current = sorted4[i];
        if(i > 0){
            int prev = sorted4[i-1];
            long long dist = manhattan_dist(current, prev);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
        if(i < N-1){
            int next = sorted4[i+1];
            long long dist = manhattan_dist(current, next);
            if(dist < points[current].min_dist){
                points[current].min_dist = dist;
            }
        }
    }

    // Find global min and max for max distance calculation
    long long minX = points[0].x, maxX = points[0].x;
    long long minY = points[0].y, maxY = points[0].y;
    for(int i=1;i<N;i++){
        if(points[i].x < minX) minX = points[i].x;
        if(points[i].x > maxX) maxX = points[i].x;
        if(points[i].y < minY) minY = points[i].y;
        if(points[i].y > maxY) maxY = points[i].y;
    }

    long long min_diff = 1e18;
    for(int i=0;i<N;i++){
        long long max_dist1 = abs(points[i].x - minX) + abs(points[i].y - minY);
        long long max_dist2 = abs(points[i].x - minX) + abs(points[i].y - maxY);
        long long max_dist3 = abs(points[i].x - maxX) + abs(points[i].y - minY);
        long long max_dist4 = abs(points[i].x - maxX) + abs(points[i].y - maxY);
        long long max_dist = max_dist1;
        if(max_dist2 > max_dist) max_dist = max_dist2;
        if(max_dist3 > max_dist) max_dist = max_dist3;
        if(max_dist4 > max_dist) max_dist = max_dist4;
        long long diff = max_dist - points[i].min_dist;
        if(diff < min_diff){
            min_diff = diff;
        }
    }

    printf("%lld\n", min_diff);

    // Free memory
    free(points);
    free(sorted1);
    free(sorted2);
    free(sorted3);
    free(sorted4);
    return 0;
}
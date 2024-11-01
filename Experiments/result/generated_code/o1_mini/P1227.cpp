#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x, y;
} Point;

int cmp_points(const void *a, const void *b) {
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if (pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    if (pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    return 0;
}

int main(){
    int N;
    if(scanf("%d", &N)!=1){
        return 0;
    }
    Point *points = (Point*)malloc(N * sizeof(Point));
    long long sum_x = 0, sum_y = 0;
    for(int i = 0; i < N; i++){
        if(scanf("%lld %lld", &points[i].x, &points[i].y)!=2){
            free(points);
            return 0;
        }
        sum_x += points[i].x;
        sum_y += points[i].y;
    }
    if((2 * sum_x) % N !=0 || (2 * sum_y) % N !=0){
        printf("This is a dangerous situation!\n");
        free(points);
        return 0;
    }
    long long double_s_x = (2 * sum_x) / N;
    long long double_s_y = (2 * sum_y) / N;
    qsort(points, N, sizeof(Point), cmp_points);
    int ok = 1;
    Point key;
    for(int i = 0; i < N && ok; i++){
        key.x = double_s_x - points[i].x;
        key.y = double_s_y - points[i].y;
        if(bsearch(&key, points, N, sizeof(Point), cmp_points) == NULL){
            ok = 0;
        }
    }
    if(ok){
        double s_x = (double)sum_x / N;
        double s_y = (double)sum_y / N;
        printf("V.I.P. should stay at (%.1lf,%.1lf).\n", s_x, s_y);
    }
    else{
        printf("This is a dangerous situation!\n");
    }
    free(points);
    return 0;
}
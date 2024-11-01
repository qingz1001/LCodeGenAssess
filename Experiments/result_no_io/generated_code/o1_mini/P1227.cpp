#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x;
    long long y;
} Point;

int cmp(const void *a, const void *b){
    Point *pa = (Point*)a;
    Point *pb = (Point*)b;
    if(pa->x != pb->x)
        return (pa->x < pb->x) ? -1 : 1;
    if(pa->y != pb->y)
        return (pa->y < pb->y) ? -1 : 1;
    return 0;
}

int find_point(Point *points, int N, long long x, long long y){
    int left = 0, right = N-1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(points[mid].x == x){
            if(points[mid].y == y){
                return 1;
            }
            // Since x is same, search in both directions
            // Search left
            int temp = mid -1;
            while(temp >= left && points[temp].x == x){
                if(points[temp].y == y) return 1;
                temp--;
            }
            // Search right
            temp = mid +1;
            while(temp <= right && points[temp].x == x){
                if(points[temp].y == y) return 1;
                temp++;
            }
            return 0;
        }
        else if(points[mid].x < x){
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    Point *points = (Point*)malloc(sizeof(Point)*N);
    long long sum_x=0, sum_y=0;
    for(int i=0;i<N;i++){
        scanf("%lld %lld", &points[i].x, &points[i].y);
        sum_x += points[i].x;
        sum_y += points[i].y;
    }
    qsort(points, N, sizeof(Point), cmp);
    for(int i=0;i<N;i++){
        long long numerator_x = 2 * sum_x - (long long)N * points[i].x;
        long long numerator_y = 2 * sum_y - (long long)N * points[i].y;
        if(numerator_x % N !=0 || numerator_y % N !=0){
            printf("This is a dangerous situation!\n");
            free(points);
            return 0;
        }
        long long sym_x = numerator_x / N;
        long long sym_y = numerator_y / N;
        if(!find_point(points, N, sym_x, sym_y)){
            printf("This is a dangerous situation!\n");
            free(points);
            return 0;
        }
    }
    double S_x = (double)sum_x / N;
    double S_y = (double)sum_y / N;
    // Rounding to one decimal
    S_x = (S_x * 10.0 + 0.5) / 10.0;
    S_y = (S_y * 10.0 + 0.5) / 10.0;
    printf("V.I.P. should stay at (%.1lf,%.1lf).\n", S_x, S_y);
    free(points);
    return 0;
}
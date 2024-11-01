#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long x, y;
} Point;

int cmp_x(const void *a, const void *b){
    Point *p = (Point*)a;
    Point *q = (Point*)b;
    if(p->x != q->x)
        return (p->x < q->x) ? -1 : 1;
    if(p->y != q->y)
        return (p->y < q->y) ? -1 : 1;
    return 0;
}

int cmp_y(const void *a, const void *b){
    Point *p = *(Point**)a;
    Point *q = *(Point**)b;
    if(p->y != q->y)
        return (p->y < q->y) ? -1 : 1;
    return 0;
}

long long distance_sq(Point a, Point b){
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx*dx + dy*dy;
}

long long closest_pair(Point points[], int left, int right){
    if(right - left <= 3){
        long long min_d = LLONG_MAX;
        for(int i=left;i<right;i++)
            for(int j=i+1;j<right;j++)
                {
                    long long d = distance_sq(points[i], points[j]);
                    if(d < min_d) min_d = d;
                }
        return min_d;
    }
    int mid = left + (right - left)/2;
    long long d1 = closest_pair(points, left, mid);
    long long d2 = closest_pair(points, mid, right);
    long long d = d1 < d2 ? d1 : d2;
    double mid_x = points[mid].x;
    
    // Collect points within sqrt(d) of mid_x
    Point* strip = malloc((right - left) * sizeof(Point));
    int s = 0;
    for(int i=left;i<right;i++) {
        double dx = points[i].x - mid_x;
        if(dx*dx < d){
            strip[s++] = points[i];
        }
    }
    // Sort strip by y
    qsort(strip, s, sizeof(Point), cmp_y);
    
    for(int i=0;i<s;i++){
        for(int j=i+1; j<s && (strip[j].y - strip[i].y)*(strip[j].y - strip[i].y) < d; j++){
            long long dist = distance_sq(strip[i], strip[j]);
            if(dist < d) d = dist;
        }
    }
    free(strip);
    return d;
}

int main(){
    int n;
    scanf("%d", &n);
    Point* points = malloc(n * sizeof(Point));
    for(int i=0;i<n;i++) scanf("%lld %lld", &points[i].x, &points[i].y);
    qsort(points, n, sizeof(Point), cmp_x);
    long long min_dist_sq = closest_pair(points, 0, n);
    double min_dist = sqrt((double)min_dist_sq);
    printf("%.4lf\n", min_dist);
    free(points);
    return 0;
}
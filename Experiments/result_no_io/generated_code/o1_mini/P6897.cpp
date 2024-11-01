#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
    double time;
} Point;

typedef struct {
    Point* points;
    int n;
} Path;

Path read_path() {
    Path path;
    scanf("%d", &path.n);
    path.points = (Point*)malloc(path.n * sizeof(Point));
    for(int i = 0; i < path.n; i++) {
        int xi, yi;
        scanf("%d %d", &xi, &yi);
        path.points[i].x = xi;
        path.points[i].y = yi;
        path.points[i].time = 0.0;
    }
    for(int i = 1; i < path.n; i++) {
        double dx = path.points[i].x - path.points[i-1].x;
        double dy = path.points[i].y - path.points[i-1].y;
        double dist = sqrt(dx*dx + dy*dy);
        path.points[i].time = path.points[i-1].time + dist;
    }
    return path;
}

Point get_position(Path* path, double t) {
    if(t >= path->points[path->n-1].time)
        return path->points[path->n-1];
    // Binary search to find the segment
    int left = 0, right = path->n - 1;
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(path->points[mid].time <= t)
            left = mid + 1;
        else
            right = mid;
    }
    left--;
    double dt = t - path->points[left].time;
    double dx = path->points[left+1].x - path->points[left].x;
    double dy = path->points[left+1].y - path->points[left].y;
    double segment_time = path->points[left+1].time - path->points[left].time;
    double ratio = dt / segment_time;
    Point pos;
    pos.x = path->points[left].x + dx * ratio;
    pos.y = path->points[left].y + dy * ratio;
    return pos;
}

double distance_point(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

int main(){
    Path A = read_path();
    Path B = read_path();
    double tA_max = A.points[A.n-1].time;
    double tB_max = B.points[B.n-1].time;
    double low = 0.0, high = tA_max + tB_max;
    double eps = 1e-7;
    double res = -1.0;
    for(int iter = 0; iter < 100; iter++){
        double mid = (low + high) / 2.0;
        // Iterate tA from 0 to tA_max, tB = tA + mid <= tB_max
        double left_tA = 0.0;
        double right_tA = fmin(tA_max, tB_max - mid);
        if(right_tA < left_tA){
            high = mid;
            continue;
        }
        int found = 0;
        // Sampling tA
        int samples = 1000;
        for(int s = 0; s <= samples; s++){
            double tA = left_tA + (right_tA - left_tA) * s / samples;
            double tB = tA + mid;
            if(tB > tB_max) continue;
            Point posA = get_position(&A, tA);
            Point posB = get_position(&B, tB);
            double dist = distance_point(posA, posB);
            if(dist <= mid + 1e-9){
                found = 1;
                break;
            }
        }
        if(found){
            res = mid;
            high = mid;
        }
        else{
            low = mid;
        }
    }
    // Verify result
    if(res < 0){
        printf("impossible\n");
    }
    else{
        // Final verification
        int valid = 0;
        double tA_max_final = A.points[A.n-1].time;
        double tB_max_final = B.points[B.n-1].time;
        double left_tA = 0.0;
        double right_tA = fmin(tA_max_final, tB_max_final - res);
        if(right_tA >= left_tA){
            int samples = 100000;
            for(int s = 0; s <= samples; s++){
                double tA = left_tA + (right_tA - left_tA) * s / samples;
                double tB = tA + res;
                if(tB > tB_max_final) continue;
                Point posA = get_position(&A, tA);
                Point posB = get_position(&B, tB);
                double dist = distance_point(posA, posB);
                if(dist <= res + 1e-6){
                    valid = 1;
                    break;
                }
            }
        }
        if(valid){
            printf("%.10lf\n", res);
        }
        else{
            printf("impossible\n");
        }
    }
    free(A.points);
    free(B.points);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

int main(){
    int N;
    scanf("%d", &N);
    Point *points = (Point*)malloc(N*sizeof(Point));
    for(int i=0;i<N;i++) scanf("%lf %lf", &points[i].x, &points[i].y);
    double min_Y = 1e18;
    for(int j=0; j<N; j++){
        double required_Y = points[j].y;
        // From left
        double max_slope = -1e18;
        for(int i=0; i<j; i++){
            double dx = points[j].x - points[i].x;
            double dy = points[j].y - points[i].y;
            double slope = dy / dx;
            if(slope > max_slope){
                max_slope = slope;
            }
            else{
                double candidate_Y = points[i].y + max_slope * dx;
                if(candidate_Y > required_Y) required_Y = candidate_Y;
            }
        }
        // From right
        max_slope = -1e18;
        for(int i=j+1; i<N; i++){
            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;
            double slope = dy / dx;
            if(slope > max_slope){
                max_slope = slope;
            }
            else{
                double candidate_Y = points[i].y - max_slope * dx;
                if(candidate_Y > required_Y) required_Y = candidate_Y;
            }
        }
        if(required_Y < min_Y) min_Y = required_Y;
    }
    printf("%.2lf\n", min_Y);
    free(points);
    return 0;
}
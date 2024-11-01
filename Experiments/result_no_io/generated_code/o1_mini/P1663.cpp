#include <stdio.h>
#include <math.h>

#define MAXN 5000
#define EPS 1e-7

typedef struct {
    double X;
    double Y;
} Point;

int N;
Point points[MAXN];

// Function to check if a given Y_light is feasible
int feasible(double Y_light) {
    for(int i = 0; i < N-1; i++) {
        double Y1 = points[i].Y;
        double Y2 = points[i+1].Y;
        double X1 = points[i].X;
        double X2 = points[i+1].X;
        // Check if Y_light is on this segment
        if ((Y1 >= Y_light && Y2 >= Y_light) || 
            (Y1 >= Y_light && Y2 <= Y_light) ||
            (Y1 <= Y_light && Y2 >= Y_light)) {
            double X_light, Y_pos;
            if (fabs(Y2 - Y1) < EPS) {
                // Horizontal segment
                X_light = X1;
                Y_pos = Y1;
                if (Y_pos < Y_light - EPS) continue;
            }
            else {
                // Find the position where Y = Y_light
                double t = (Y_light - Y1) / (Y2 - Y1);
                if (t < -EPS || t > 1 + EPS) continue;
                X_light = X1 + t * (X2 - X1);
                Y_pos = Y_light;
            }

            // Check visibility to the left
            double max_slope_left = -1e20;
            int blocked = 0;
            for(int j = 0; j < N; j++) {
                if(points[j].X >= X_light) break;
                double slope = (Y_pos - points[j].Y) / (X_light - points[j].X);
                if(slope < max_slope_left - EPS){
                    blocked = 1;
                    break;
                }
                if(slope > max_slope_left){
                    max_slope_left = slope;
                }
            }
            if(blocked) continue;

            // Check visibility to the right
            double max_slope_right = -1e20;
            blocked = 0;
            for(int j = N-1; j >=0; j--){
                if(points[j].X <= X_light) continue;
                double slope = (points[j].Y - Y_pos) / (points[j].X - X_light);
                if(slope < max_slope_right - EPS){
                    blocked = 1;
                    break;
                }
                if(slope > max_slope_right){
                    max_slope_right = slope;
                }
            }
            if(blocked) continue;

            // If both sides are visible
            return 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &N);
    for(int i =0;i<N;i++) scanf("%lf %lf", &points[i].X, &points[i].Y);
    double low = 0.0, high = 1000000.0, mid, ans = high;
    for(int iter=0; iter<50; iter++){
        mid = (low + high) / 2.0;
        if(feasible(mid)){
            ans = mid;
            high = mid;
        }
        else{
            low = mid;
        }
    }
    printf("%.2lf\n", ans);
    return 0;
}
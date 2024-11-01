#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_ITER 10000
#define EPS 1e-9

typedef struct {
    double xi, yi, wi;
} Hole;

int main(){
    int n;
    scanf("%d", &n);
    Hole holes[n];
    double sum_w = 0.0, sum_wx = 0.0, sum_wy = 0.0;
    for(int i=0;i<n;i++){
        scanf("%lf %lf %lf", &holes[i].xi, &holes[i].yi, &holes[i].wi);
        sum_w += holes[i].wi;
        sum_wx += holes[i].wi * holes[i].xi;
        sum_wy += holes[i].wi * holes[i].yi;
    }
    double X = sum_wx / sum_w;
    double Y = sum_wy / sum_w;
    for(int iter=0; iter<MAX_ITER; iter++){
        double F=0.0, G=0.0;
        double dFdx=0.0, dFdy=0.0, dGdx=0.0, dGdy=0.0;
        for(int i=0;i<n;i++){
            double dx = X - holes[i].xi;
            double dy = Y - holes[i].yi;
            double dist = sqrt(dx*dx + dy*dy);
            if(dist < EPS){
                continue;
            }
            double w_over_d = holes[i].wi / dist;
            F += w_over_d * dx;
            G += w_over_d * dy;
            double d = dist;
            double d3 = d * d * d;
            dFdx += holes[i].wi * (d - dx * dx / d) / (d * d);
            dFdy += -holes[i].wi * (dx * dy) / (d3);
            dGdx += -holes[i].wi * (dx * dy) / (d3);
            dGdy += holes[i].wi * (d - dy * dy / d) / (d * d);
        }
        double det = dFdx * dGdy - dFdy * dGdx;
        if(fabs(det) < EPS){
            break;
        }
        double deltaX = (-F * dGdy + F * dFdy) / det;
        double deltaY = (-dFdx * G + dFdx * G) / det;
        // Alternatively, solve:
        double a = dFdx, b = dFdy, c = dGdx, d = dGdy;
        double e = -F, f = -G;
        double determinant = a * d - b * c;
        if(fabs(determinant) < EPS){
            break;
        }
        double delta_x = (d * e - b * f) / determinant;
        double delta_y = (-c * e + a * f) / determinant;
        X += delta_x;
        Y += delta_y;
        if(fabs(delta_x) < EPS && fabs(delta_y) < EPS){
            break;
        }
    }
    printf("%.3lf %.3lf\n", X, Y);
    return 0;
}
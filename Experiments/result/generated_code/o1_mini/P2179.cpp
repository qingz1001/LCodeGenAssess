#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double s;
    double k;
    double vp;
} Segment;

int main(){
    int n;
    double E_U;
    if(scanf("%d %lf", &n, &E_U)!=2){
        return 1;
    }
    Segment *seg = (Segment*)malloc(n * sizeof(Segment));
    for(int i=0;i<n;i++) {
        if(scanf("%lf %lf %lf", &seg[i].s, &seg[i].k, &seg[i].vp)!=3){
            free(seg);
            return 1;
        }
    }
    double lo = 0.0, hi = 1e14, lambda=0.0;
    double epsilon = 1e-8;
    int max_iter = 100;
    double sum_E, sum_T;
    for(int it=0; it<max_iter; it++){
        lambda = (lo + hi) / 2.0;
        sum_E = 0.0;
        sum_T = 0.0;
        for(int i=0;i<n;i++){
            double v = seg[i].vp > 0.0 ? seg[i].vp : 1.0;
            if(v < 1e-6) v = 1.0;
            // Newton-Raphson iterations
            for(int j=0; j<10; j++){
                double f = 2.0 * lambda * seg[i].k * v * v * v - 2.0 * lambda * seg[i].k * seg[i].vp * v * v - 1.0;
                double fd = 6.0 * lambda * seg[i].k * v * v - 4.0 * lambda * seg[i].k * seg[i].vp * v;
                if(fabs(fd) < 1e-12) break;
                double dv = f / fd;
                v -= dv;
                if(v < 1e-6){
                    v = 1e-6;
                    break;
                }
                if(fabs(dv) < 1e-12) break;
            }
            sum_E += seg[i].k * (v - seg[i].vp) * (v - seg[i].vp) * seg[i].s;
            sum_T += seg[i].s / v;
        }
        if(sum_E > E_U){
            lo = lambda;
        }
        else{
            hi = lambda;
        }
        if(hi - lo < epsilon){
            break;
        }
    }
    // Compute final T with the found lambda
    lambda = (lo + hi) / 2.0;
    sum_T = 0.0;
    for(int i=0;i<n;i++){
        double v = seg[i].vp > 0.0 ? seg[i].vp : 1.0;
        if(v < 1e-6) v = 1.0;
        // Newton-Raphson iterations
        for(int j=0; j<10; j++){
            double f = 2.0 * lambda * seg[i].k * v * v * v - 2.0 * lambda * seg[i].k * seg[i].vp * v * v - 1.0;
            double fd = 6.0 * lambda * seg[i].k * v * v - 4.0 * lambda * seg[i].k * seg[i].vp * v;
            if(fabs(fd) < 1e-12) break;
            double dv = f / fd;
            v -= dv;
            if(v < 1e-6){
                v = 1e-6;
                break;
            }
            if(fabs(dv) < 1e-12) break;
        }
        sum_T += seg[i].s / v;
    }
    printf("%.10lf\n", sum_T);
    free(seg);
    return 0;
}
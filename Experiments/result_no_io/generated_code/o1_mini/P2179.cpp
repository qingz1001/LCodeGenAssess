#include <stdio.h>
#include <math.h>

typedef struct {
    double s;
    double k;
    double vp;
} Segment;

int main(){
    int n;
    double E_U;
    scanf("%d %lf", &n, &E_U);
    Segment segs[n];
    for(int i=0;i<n;i++) {
        scanf("%lf %lf %lf", &segs[i].s, &segs[i].k, &segs[i].vp);
    }

    double low = 1e-12, high = 1e12;
    double eps = 1e-14;
    double lambda, sum_E, sum_T;
    for(int it=0; it<100; it++){
        lambda = (low + high) / 2.0;
        sum_E = 0.0;
        for(int i=0;i<n;i++){
            double si = segs[i].s;
            double ki = segs[i].k;
            double vpi = segs[i].vp;
            double ci = si / (2.0 * lambda * ki);
            // Solve v^3 - vpi*v^2 - ci =0
            double left = 0.0, right = 1e12;
            double vi = 0.0;
            for(int j=0; j<50; j++){
                double mid = (left + right) / 2.0;
                double f = mid * mid * mid - vpi * mid * mid - ci;
                if(f < 0.0){
                    left = mid;
                }
                else{
                    right = mid;
                }
            }
            vi = (left + right) / 2.0;
            sum_E += ki * (vi - vpi) * (vi - vpi) * si;
        }
        if(sum_E > E_U){
            low = lambda;
        }
        else{
            high = lambda;
        }
    }
    // Compute final sum_T with lambda=high
    lambda = high;
    sum_T = 0.0;
    for(int i=0;i<n;i++){
        double si = segs[i].s;
        double ki = segs[i].k;
        double vpi = segs[i].vp;
        double ci = si / (2.0 * lambda * ki);
        // Solve v^3 - vpi*v^2 - ci =0
        double left = 0.0, right = 1e12;
        double vi = 0.0;
        for(int j=0; j<50; j++){
            double mid = (left + right) / 2.0;
            double f = mid * mid * mid - vpi * mid * mid - ci;
            if(f < 0.0){
                left = mid;
            }
            else{
                right = mid;
            }
        }
        vi = (left + right) / 2.0;
        sum_T += si / vi;
    }
    printf("%.10lf\n", sum_T);
    return 0;
}
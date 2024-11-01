#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 80005
#define MAX_M 80005
#define MAX_Q 300005

typedef struct {
    double x;
    double y;
    double t;
} Move;

typedef struct {
    double t_start;
    double t_end;
    double dx0;
    double dy0;
    double dvx;
    double dvy;
} Interval;

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    
    double Ax0, Ay0, Bx0, By0;
    scanf("%lf %lf %lf %lf", &Ax0, &Ay0, &Bx0, &By0);
    
    Move A[MAX_N];
    A[0].x = Ax0;
    A[0].y = Ay0;
    A[0].t = 0.0;
    for(int i=1;i<=n;i++) {
        scanf("%lf %lf %lf", &A[i].x, &A[i].y, &A[i].t);
    }
    
    Move Y[MAX_M];
    Y[0].x = Bx0;
    Y[0].y = By0;
    Y[0].t = 0.0;
    for(int i=1;i<=m;i++) {
        scanf("%lf %lf %lf", &Y[i].x, &Y[i].y, &Y[i].t);
    }
    
    // Merge intervals
    int i=0, j=0;
    int interval_cnt=0;
    Interval intervals[MAX_N + MAX_M];
    while(i < n || j < m){
        double current_t_start = A[i].t;
        double current_y_start = Y[j].t;
        double next_t_a = (i < n) ? A[i+1].t : 1e18;
        double next_t_y = (j < m) ? Y[j+1].t : 1e18;
        double current_t_end = next_t_a < next_t_y ? next_t_a : next_t_y;
        
        // Relative positions at current_t_start
        double dt_a = current_t_start - A[i].t;
        double Ax = A[i].x;
        double Ay = A[i].y;
        if(i < n && current_t_start < A[i+1].t){
            // Velocity for A
            // Not needed here, will compute relative velocities below
        }
        
        double dt_y = current_t_start - Y[j].t;
        double Bx = Y[j].x;
        double By = Y[j].y;
        
        // Compute relative position and velocity
        double rx = A[i].x - Y[j].x;
        double ry = A[i].y - Y[j].y;
        double rvx = 0.0, rvy = 0.0;
        if(i < n){
            rvx += (A[i+1].x - A[i].x)/(A[i+1].t - A[i].t);
            rvy += (A[i+1].y - A[i].y)/(A[i+1].t - A[i].t);
        }
        if(j < m){
            rvx -= (Y[j+1].x - Y[j].x)/(Y[j+1].t - Y[j].t);
            rvy -= (Y[j+1].y - Y[j].y)/(Y[j+1].t - Y[j].t);
        }
        
        intervals[interval_cnt].t_start = current_t_start;
        intervals[interval_cnt].t_end = current_t_end;
        intervals[interval_cnt].dx0 = rx;
        intervals[interval_cnt].dy0 = ry;
        intervals[interval_cnt].dvx = rvx;
        intervals[interval_cnt].dvy = rvy;
        interval_cnt++;
        
        if(next_t_a < next_t_y){
            i++;
        }
        else{
            j++;
        }
    }
    
    // Read all queries
    double c_q[MAX_Q];
    int f_q[MAX_Q];
    for(int qi=0; qi<q; qi++){
        scanf("%lf %d", &c_q[qi], &f_q[qi]);
    }
    
    // Process each query
    for(int qi=0; qi<q; qi++){
        double c = c_q[qi];
        double csq = c * c;
        int f = f_q[qi];
        int count = 0;
        double ans = -4.66;
        int infinite = 0;
        for(int k=0; k<interval_cnt; k++){
            Interval itv = intervals[k];
            double a = itv.dvx * itv.dvx + itv.dvy * itv.dvy;
            double b = 2.0 * (itv.dx0 * itv.dvx + itv.dy0 * itv.dvy);
            double c_eq = itv.dx0 * itv.dx0 + itv.dy0 * itv.dy0 - csq;
            if(fabs(a) < 1e-12){
                if(fabs(b) < 1e-12){
                    if(fabs(c_eq) < 1e-12){
                        infinite = 1;
                        break;
                    }
                }
                else{
                    double t = -c_eq / b + itv.t_start;
                    if(t >= itv.t_start - 1e-9 && t <= itv.t_end + 1e-9){
                        if(count +1 == f){
                            ans = t;
                            break;
                        }
                        count++;
                    }
                }
            }
            else{
                double disc = b * b - 4.0 * a * c_eq;
                if(disc < -1e-8) continue;
                if(disc < 0.0) disc = 0.0;
                double sqrt_disc = sqrt(disc);
                double t1 = (-b - sqrt_disc) / (2.0 * a) + itv.t_start;
                double t2 = (-b + sqrt_disc) / (2.0 * a) + itv.t_start;
                if(t1 >= itv.t_start - 1e-9 && t1 <= itv.t_end + 1e-9){
                    if(count +1 == f){
                        ans = t1;
                        break;
                    }
                    count++;
                }
                if(t2 >= itv.t_start - 1e-9 && t2 <= itv.t_end + 1e-9 && fabs(t2 - t1) > 1e-9){
                    if(count +1 == f){
                        ans = t2;
                        break;
                    }
                    count++;
                }
            }
        }
        if(infinite){
            printf("-2.33\n");
        }
        else if(count < f){
            printf("-4.66\n");
        }
        else{
            printf("%.8lf\n", ans);
        }
    }
    return 0;
}
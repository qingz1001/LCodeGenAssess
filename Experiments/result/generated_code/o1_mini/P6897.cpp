#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

typedef struct {
    double t_start, t_end;
    double x_start, y_start;
    double vx, vy;
} Segment;

int main(){
    int n, m;
    scanf("%d", &n);
    Point *A_points = (Point*)malloc(n * sizeof(Point));
    for(int i=0;i<n;i++) scanf("%lf %lf", &A_points[i].x, &A_points[i].y);
    // Build A's segments
    int num_a = n - 1;
    Segment *A = (Segment*)malloc(num_a * sizeof(Segment));
    double time_a = 0.0;
    for(int i=0;i<num_a;i++){
        double dx = A_points[i+1].x - A_points[i].x;
        double dy = A_points[i+1].y - A_points[i].y;
        double length = sqrt(dx*dx + dy*dy);
        A[i].t_start = time_a;
        A[i].t_end = time_a + length;
        A[i].x_start = A_points[i].x;
        A[i].y_start = A_points[i].y;
        if(length ==0){
            A[i].vx = 0;
            A[i].vy = 0;
        }
        else{
            A[i].vx = dx / length;
            A[i].vy = dy / length;
        }
        time_a += length;
    }
    double T_A = time_a;
    free(A_points);
    scanf("%d", &m);
    Point *B_points = (Point*)malloc(m * sizeof(Point));
    for(int i=0;i<m;i++) scanf("%lf %lf", &B_points[i].x, &B_points[i].y);
    // Build B's segments
    int num_b = m -1;
    Segment *B = (Segment*)malloc(num_b * sizeof(Segment));
    double time_b = 0.0;
    for(int i=0;i<num_b;i++){
        double dx = B_points[i+1].x - B_points[i].x;
        double dy = B_points[i+1].y - B_points[i].y;
        double length = sqrt(dx*dx + dy*dy);
        B[i].t_start = time_b;
        B[i].t_end = time_b + length;
        B[i].x_start = B_points[i].x;
        B[i].y_start = B_points[i].y;
        if(length ==0){
            B[i].vx = 0;
            B[i].vy = 0;
        }
        else{
            B[i].vx = dx / length;
            B[i].vy = dy / length;
        }
        time_b += length;
    }
    double T_B = time_b;
    free(B_points);
    // Binary search
    double low = 0.0, high = T_B;
    double ans = -1.0;
    int feasible = 0;
    for(int iter=0; iter<100; iter++){
        double mid = (low + high) / 2.0;
        // Check feasibility for delta = mid
        double delta = mid;
        if(delta > T_B) { low = mid; continue; }
        // Iterate A and B segments
        int idx_a = 0, idx_b =0;
        double feasible_found = 0.0;
        while(idx_a < num_a && (A[idx_a].t_start <= T_A)){
            // t_A ranges from A[idx_a].t_start to A[idx_a].t_end
            double t_A_start = A[idx_a].t_start;
            double t_A_end = A[idx_a].t_end;
            // t_B = t_A + delta must be <= T_B
            double t_A_max = T_B - delta;
            if(t_A_max < t_A_start) { idx_a++; continue; }
            double left = t_A_start;
            double right = t_A_end;
            if(right > t_A_max) right = t_A_max;
            if(left > right){
                idx_a++;
                continue;
            }
            // Find B's segment for t_B = t_A + delta
            // Binary search to find idx_b such that B[idx_b].t_start <= t_A + delta < B[idx_b].t_end
            double t_B_left = left + delta;
            double t_B_right = right + delta;
            // Find starting idx_b
            while(idx_b < num_b && B[idx_b].t_end <= t_B_left) idx_b++;
            if(idx_b >= num_b) { idx_a++; continue; }
            int current_b = idx_b;
            while(current_b < num_b && B[current_b].t_start < t_B_right){
                // Overlapping interval
                double seg_B_start = B[current_b].t_start;
                double seg_B_end = B[current_b].t_end;
                double overlap_left_t_A = left;
                double overlap_right_t_A = right;
                double overlap_t_B_start = seg_B_start;
                double overlap_t_B_end = seg_B_end;
                // t_B = t_A + delta
                // so t_A = t_B - delta
                double tmp_left = seg_B_start - delta;
                double tmp_right = seg_B_end - delta;
                if(tmp_left > overlap_left_t_A) overlap_left_t_A = tmp_left;
                if(tmp_right < overlap_right_t_A) overlap_right_t_A = tmp_right;
                if(overlap_left_t_A > overlap_right_t_A){
                    current_b++;
                    continue;
                }
                double l = overlap_left_t_A;
                double r = overlap_right_t_A;
                // A's velocity
                double vax = A[idx_a].vx;
                double vay = A[idx_a].vy;
                // B's velocity
                double vbx = B[current_b].vx;
                double vby = B[current_b].vy;
                // Relative velocity
                double dvx = vax - vbx;
                double dvy = vay - vby;
                // Relative position at t_A =0
                double Ax = A[idx_a].x_start;
                double Ay = A[idx_a].y_start;
                double Bx = B[current_b].x_start + vbx*(delta);
                double By = B[current_b].y_start + vby*(delta);
                // Position difference: (Ax + dvx*(t_A - A[idx_a].t_start)) - Bx
                // Simplify as Ax' + dvx * t_A, Ay' + dvy * t_A
                double px = Ax - Bx + dvx * l;
                double py = Ay - By + dvy * l;
                // f(t_A) = (px + dvx*(t_A - l))^2 + (py + dvy*(t_A - l))^2
                // But to simplify, f(t_A) = (Ax(l) - Bx(t_A + delta))^2 + (Ay(l) - By(t_A + delta))^2
                // Which is (px + dvx*(t_A - l))^2 + (py + dvy*(t_A - l))^2
                // Which simplifies to (dvx)^2 * (t_A - l)^2 + 2*dvx*px*(t_A - l) + px^2
                // + (dvy)^2 * (t_A - l)^2 + 2*dvy*py*(t_A - l) + py^2
                // = (dvx^2 + dvy^2) * t_A^2 + ( -2*dvx^2*l -2*dvy^2*l + 2*dvx*px + 2*dvy*py )*t_A
                // + (dvx^2*l*l - 2*dvx*px*l + px*px + dvy^2*l*l - 2*dvy*py*l + py*py )
                double A_coef = dvx * dvx + dvy * dvy;
                double B_coef = -2.0 * (dvx * dvx + dvy * dvy) * l + 2.0 * (dvx * px + dvy * py);
                double C_coef = dvx * dvx * l * l - 2.0 * dvx * px * l + px * px + dvy * dvy * l * l - 2.0 * dvy * py * l + py * py;
                // f(t_A) = A_coef * t_A * t_A + B_coef * t_A + C_coef
                // We need f(t_A) <= delta * delta
                // f(t_A) - delta^2 <= 0
                double A_q = A_coef;
                double B_q = B_coef;
                double C_q = C_coef - delta * delta;
                // Find minimum of f(t_A) in [l, r]
                double t_min = -B_q / (2.0 * A_q);
                double f_min;
                if(A_q ==0){
                    f_min = C_q + B_q * l;
                }
                else{
                    if(t_min < l) t_min = l;
                    if(t_min > r) t_min = r;
                    f_min = A_q * t_min * t_min + B_q * t_min + C_q;
                }
                // Check endpoints
                double f_l = A_q * l * l + B_q * l + C_q;
                double f_r = A_q * r * r + B_q * r + C_q;
                if(f_min <= 0.0 || f_l <=0.0 || f_r <=0.0){
                    feasible_found = 1.0;
                    break;
                }
                current_b++;
            }
            if(feasible_found) break;
            idx_a++;
        }
        if(feasible_found){
            feasible =1;
            ans = delta;
            high = mid;
        }
        else{
            low = mid;
        }
    }
    // Final check
    // Check if ans is feasible
    // If no feasible delta found within T_B, output impossible
    // Else, output ans with 5 decimal places
    // To handle floating precision, perform a final check
    // Here, assume that if ans was set, it's feasible
    if(feasible && ans <= T_B){
        printf("%.5lf\n", ans);
    }
    else{
        printf("impossible\n");
    }
    free(A);
    free(B);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    double Ax;
    double Ay;
    double At;
} AMove;

typedef struct {
    double Bx;
    double By;
    double Bt;
} YMove;

typedef struct {
    double t_start;
    double t_end;
    double A;
    double B;
    double C;
} Interval;

typedef struct {
    int c_int;
    int f;
    int index;
} Query;

int cmp_query(const void *a, const void *b){
    Query *qa = (Query *)a;
    Query *qb = (Query *)b;
    if(qa->c_int != qb->c_int){
        return qa->c_int - qb->c_int;
    }
    return 0;
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    double Ax0, Ay0, Bx0, By0;
    scanf("%lf %lf %lf %lf", &Ax0, &Ay0, &Bx0, &By0);
    AMove *A = (AMove *)malloc((n+1)*sizeof(AMove));
    A[0].Ax = Ax0;
    A[0].Ay = Ay0;
    A[0].At = 0.0;
    for(int i=1;i<=n;i++) {
        scanf("%lf %lf %lf", &A[i].Ax, &A[i].Ay, &A[i].At);
    }
    YMove *Y = (YMove *)malloc((m+1)*sizeof(YMove));
    Y[0].Bx = Bx0;
    Y[0].By = By0;
    Y[0].Bt = 0.0;
    for(int i=1;i<=m;i++) {
        scanf("%lf %lf %lf", &Y[i].Bx, &Y[i].By, &Y[i].Bt);
    }
    Query *queries = (Query *)malloc(q * sizeof(Query));
    for(int i=0;i<q;i++) {
        double c;
        int f;
        scanf("%lf %d", &c, &f);
        int c_int = (int)(c * 100.0 + 0.5);
        queries[i].c_int = c_int;
        queries[i].f = f;
        queries[i].index = i;
    }
    // Sort queries by c_int
    qsort(queries, q, sizeof(Query), cmp_query);
    // Merge intervals
    int i_a=0, i_y=0;
    int total_intervals = 0;
    Interval *intervals = (Interval *)malloc((n+m+2)*sizeof(Interval));
    while(i_a < n && i_y < m){
        double start = A[i_a].At > Y[i_y].Bt ? A[i_a].At : Y[i_y].Bt;
        double end_a = A[i_a+1].At;
        double end_y = Y[i_y+1].Bt;
        double end = end_a < end_y ? end_a : end_y;
        if(end > start){
            double duration_a = A[i_a+1].At - A[i_a].At;
            double vx_a = duration_a > 1e-9 ? (A[i_a+1].Ax - A[i_a].Ax)/duration_a : 0.0;
            double vy_a = duration_a > 1e-9 ? (A[i_a+1].Ay - A[i_a].Ay)/duration_a : 0.0;
            double duration_y = Y[i_y+1].Bt - Y[i_y].Bt;
            double vx_y = duration_y > 1e-9 ? (Y[i_y+1].Bx - Y[i_y].Bx)/duration_y : 0.0;
            double vy_y = duration_y > 1e-9 ? (Y[i_y+1].By - Y[i_y].By)/duration_y : 0.0;
            double dx = A[i_a].Ax - Y[i_y].Bx;
            double dy = A[i_a].Ay - Y[i_y].By;
            double dvx = vx_a - vx_y;
            double dvy = vy_a - vy_y;
            double A_coef = dvx * dvx + dvy * dvy;
            double B_coef = 2.0 * (dx * dvx + dy * dvy);
            double C_coef = dx * dx + dy * dy;
            intervals[total_intervals].t_start = start;
            intervals[total_intervals].t_end = end;
            intervals[total_intervals].A = A_coef;
            intervals[total_intervals].B = B_coef;
            intervals[total_intervals].C = C_coef;
            total_intervals++;
        }
        if(end_a < end_y){
            i_a++;
        }
        else{
            i_y++;
        }
    }
    // Prepare answers
    double *answers = (double *)malloc(q * sizeof(double));
    // Process queries
    int current =0;
    while(current < q){
        int current_c = queries[current].c_int;
        // Find the range of queries with current_c
        int start_q = current;
        while(current < q && queries[current].c_int == current_c){
            current++;
        }
        int end_q = current;
        double c = current_c / 100.0;
        double c_sq = c * c;
        int flag_infinite = 0;
        // Collect t's
        // Allocate temporary array
        double *t_list = (double *)malloc(2 * total_intervals * sizeof(double));
        int t_count =0;
        for(int k=0;k<total_intervals && !flag_infinite;k++){
            double A_coef = intervals[k].A;
            double B_coef = intervals[k].B;
            double C_coef = intervals[k].C;
            double t_start = intervals[k].t_start;
            double t_end = intervals[k].t_end;
            if(fabs(A_coef) < 1e-12 && fabs(B_coef) <1e-12){
                if(fabs(C_coef - c_sq) <=1e-7){
                    flag_infinite=1;
                    break;
                }
                else{
                    continue;
                }
            }
            if(fabs(A_coef) <1e-12){
                if(fabs(B_coef) <1e-12){
                    continue;
                }
                double t = -(C_coef - c_sq)/B_coef;
                if(t_start - 1e-9 <= t && t <= t_end +1e-9){
                    t_list[t_count++] = t;
                }
                continue;
            }
            double delta = B_coef * B_coef - 4.0 * A_coef * (C_coef - c_sq);
            if(delta < -1e-7){
                continue;
            }
            if(delta <0){
                delta =0.0;
            }
            double sqrt_delta = sqrt(delta);
            double t1 = (-B_coef - sqrt_delta)/(2.0 * A_coef);
            double t2 = (-B_coef + sqrt_delta)/(2.0 * A_coef);
            if(t_start -1e-9 <= t1 && t1 <= t_end +1e-9){
                t_list[t_count++] = t1;
            }
            if(t_start -1e-9 <= t2 && t2 <= t_end +1e-9 && fabs(t2 - t1) >1e-9){
                t_list[t_count++] = t2;
            }
        }
        if(flag_infinite){
            for(int k=start_q; k<end_q; k++){
                answers[queries[k].index] = -2.33;
            }
            free(t_list);
            continue;
        }
        // Sort t_list
        if(t_count >0){
            // Since intervals are processed in order and t's within intervals are sorted, t_list is already sorted
            // No need to sort
        }
        for(int k=start_q; k<end_q; k++){
            int f = queries[k].f;
            if(f <= t_count){
                // Find the f-th smallest t
                // Since t_list is already sorted
                // To ensure precision, iterate and count
                double t_ans = t_list[f-1];
                answers[queries[k].index] = t_ans;
            }
            else{
                answers[queries[k].index] = -4.66;
            }
        }
        free(t_list);
    }
    // Output answers
    for(int i=0;i<q;i++){
        if(answers[i] == -2.33){
            printf("-2.33\n");
        }
        else if(answers[i] == -4.66){
            printf("-4.66\n");
        }
        else{
            printf("%.10lf\n", answers[i]);
        }
    }
    // Free memory
    free(A);
    free(Y);
    free(intervals);
    free(queries);
    free(answers);
    return 0;
}
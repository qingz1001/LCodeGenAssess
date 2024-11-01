#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double wi;
    double xi;
    double yi;
    double pi;
    double qi;
    double earliest_t;
    int index;
} Shrimp;

typedef struct {
    double t;
    double x;
    double y;
    int s;
} Eat;

int cmp(const void *a, const void *b){
    Shrimp *sa = (Shrimp*)a;
    Shrimp *sb = (Shrimp*)b;
    if (sa->earliest_t < sb->earliest_t) return -1;
    if (sa->earliest_t > sb->earliest_t) return 1;
    return sa->index - sb->index;
}

int main(){
    double w0, V, T, x0, y0;
    scanf("%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    int n;
    scanf("%d", &n);
    Shrimp shrimps[n];
    for(int i=0;i<n;i++){
        scanf("%lf %lf %lf %lf %lf", &shrimps[i].wi, &shrimps[i].xi, &shrimps[i].yi, &shrimps[i].pi, &shrimps[i].qi);
        shrimps[i].earliest_t = T + 1.0;
        shrimps[i].index = i+1;
        double A = shrimps[i].pi*shrimps[i].pi + shrimps[i].qi*shrimps[i].qi - V*V;
        double B = 2.0*((shrimps[i].xi - x0)*shrimps[i].pi + (shrimps[i].yi - y0)*shrimps[i].qi);
        double C = (shrimps[i].xi - x0)*(shrimps[i].xi - x0) + (shrimps[i].yi - y0)*(shrimps[i].yi - y0);
        if (fabs(A) < 1e-8){
            if (fabs(B) <1e-8){
                if (C <=0){
                    shrimps[i].earliest_t = 0.0;
                }
            }
            else{
                double t = -C/B;
                if (t >=0 && t <= T){
                    shrimps[i].earliest_t = t;
                }
            }
        }
        else{
            double discriminant = B*B - 4*A*C;
            if (discriminant >= -1e-8){
                if(discriminant <0) discriminant =0;
                double sqrtD = sqrt(discriminant);
                double t1 = (-B - sqrtD)/(2*A);
                double t2 = (-B + sqrtD)/(2*A);
                if (A >0){
                    if(t1 >=0 && t1 <= T){
                        shrimps[i].earliest_t = t1;
                    }
                    if(t2 >=0 && t2 <= T && t2 < shrimps[i].earliest_t){
                        shrimps[i].earliest_t = t2;
                    }
                }
                else{
                    if(t1 >=0 && t1 <= T && t1 < shrimps[i].earliest_t){
                        shrimps[i].earliest_t = t1;
                    }
                    if(t2 >=0 && t2 <= T && t2 < shrimps[i].earliest_t){
                        shrimps[i].earliest_t = t2;
                    }
                }
            }
        }
    }
    qsort(shrimps, n, sizeof(Shrimp), cmp);
    // Initialize DP
    double dp[n];
    int prev[n];
    for(int i=0;i<n;i++){
        dp[i] = 0.0;
        prev[i] = -1;
    }
    for(int i=0;i<n;i++){
        // Check if can reach directly from start
        double t = shrimps[i].earliest_t;
        if(t > T) continue;
        double sx = shrimps[i].xi + shrimps[i].pi * t;
        double sy = shrimps[i].yi + shrimps[i].qi * t;
        double dist = sqrt((sx - x0)*(sx - x0) + (sy - y0)*(sy - y0));
        if(dist <= V * t && w0 > shrimps[i].wi){
            if(dp[i] < shrimps[i].wi){
                dp[i] = shrimps[i].wi;
                prev[i] = -1;
            }
        }
        // Check from previous shrimps
        for(int j=0;j<i;j++){
            if(dp[j] > 0.0){
                double prev_t = shrimps[j].earliest_t;
                double current_t = shrimps[i].earliest_t;
                if(current_t < prev_t) continue;
                double sx_prev = shrimps[j].xi + shrimps[j].pi * prev_t;
                double sy_prev = shrimps[j].yi + shrimps[j].qi * prev_t;
                double sx_curr = shrimps[i].xi + shrimps[i].pi * current_t;
                double sy_curr = shrimps[i].yi + shrimps[i].qi * current_t;
                double move_dist = sqrt((sx_curr - sx_prev)*(sx_curr - sx_prev) + (sy_curr - sy_prev)*(sy_curr - sy_prev));
                double time_diff = current_t - prev_t;
                if(move_dist <= V * time_diff && dp[j] > shrimps[i].wi){
                    if(dp[i] < dp[j] + shrimps[i].wi){
                        dp[i] = dp[j] + shrimps[i].wi;
                        prev[i] = j;
                    }
                }
            }
        }
    }
    // Find the maximum
    double max_w = 0.0;
    int last = -1;
    for(int i=0;i<n;i++){
        if(dp[i] > max_w){
            max_w = dp[i];
            last = i;
        }
    }
    // Reconstruct the path
    int path_size =0;
    int path_indices[n];
    while(last != -1){
        path_indices[path_size++] = last;
        last = prev[last];
    }
    // Print the output
    printf("%d\n", path_size);
    printf("%.6lf\n", max_w);
    for(int i=path_size-1;i>=0;i--){
        int idx = path_indices[i];
        double t = shrimps[idx].earliest_t;
        double x = shrimps[idx].xi + shrimps[idx].pi * t;
        double y = shrimps[idx].yi + shrimps[idx].qi * t;
        printf("%.6lf %.6lf %.6lf %d\n", t, x, y, shrimps[idx].index);
    }
    return 0;
}
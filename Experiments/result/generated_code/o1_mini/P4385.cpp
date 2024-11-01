#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double angle;
} Angle;

typedef struct {
    double proj;
    char color;
} PointProj;

// Comparator for angles
int cmp_angle(const void *a, const void *b){
    double diff = ((Angle*)a)->angle - ((Angle*)b)->angle;
    if(diff < 0) return -1;
    else if(diff > 0) return 1;
    else return 0;
}

// Comparator for projections
int cmp_proj(const void *a, const void *b){
    double diff = ((PointProj*)a)->proj - ((PointProj*)b)->proj;
    if(diff < 0) return -1;
    else if(diff > 0) return 1;
    else return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    long long *x = (long long*)malloc(N * sizeof(long long));
    long long *y = (long long*)malloc(N * sizeof(long long));
    char *c = (char*)malloc(N * sizeof(char));
    for(int i=0;i<N;i++) {
        scanf("%lld %lld %c", &x[i], &y[i], &c[i]);
    }

    // Generate all possible angles
    int max_angles = N * (N -1) /2;
    Angle *angles = (Angle*)malloc(max_angles * sizeof(Angle));
    int count =0;
    for(int i=0;i<N;i++) {
        for(int j=i+1;j<N;j++) {
            long long dx = x[j] - x[i];
            long long dy = y[j] - y[i];
            // Perpendicular direction: (-dy, dx)
            double angle = atan2((double)dx, (double)(-dy));
            if(angle < 0) angle += M_PI;
            else if(angle >= M_PI) angle -= M_PI;
            angles[count++].angle = angle;
        }
    }

    // Sort angles
    qsort(angles, count, sizeof(Angle), cmp_angle);

    // Remove duplicate angles within epsilon
    double epsilon = 1e-9;
    Angle *unique_angles = (Angle*)malloc(count * sizeof(Angle));
    int unique_count =0;
    if(count >0){
        unique_angles[unique_count++] = angles[0];
        for(int i=1;i<count;i++) {
            if(fabs(angles[i].angle - angles[i-1].angle) > epsilon){
                unique_angles[unique_count++] = angles[i];
            }
        }
    }

    free(angles);

    // Now iterate over unique angles
    int max_red =0;
    PointProj *projs = (PointProj*)malloc(N * sizeof(PointProj));
    for(int i=0;i<unique_count;i++){
        double theta = unique_angles[i].angle;
        double cos_theta = cos(theta);
        double sin_theta = sin(theta);
        for(int j=0;j<N;j++) {
            projs[j].proj = x[j]*cos_theta + y[j]*sin_theta;
            projs[j].color = c[j];
        }
        qsort(projs, N, sizeof(PointProj), cmp_proj);
        // Sliding window: only red points, reset when blue encountered
        int current_red =0;
        for(int j=0;j<N;j++) {
            if(projs[j].color == 'B'){
                current_red =0;
            }
            else{
                current_red++;
                if(current_red > max_red) max_red = current_red;
            }
        }
    }

    // Additionally, consider vertical and horizontal angles
    // To ensure no missing directions
    // Horizontal
    {
        double theta = 0.0;
        double cos_theta = cos(theta);
        double sin_theta = sin(theta);
        for(int j=0;j<N;j++) {
            projs[j].proj = x[j]*cos_theta + y[j]*sin_theta;
            projs[j].color = c[j];
        }
        qsort(projs, N, sizeof(PointProj), cmp_proj);
        int current_red =0;
        for(int j=0;j<N;j++) {
            if(projs[j].color == 'B'){
                current_red =0;
            }
            else{
                current_red++;
                if(current_red > max_red) max_red = current_red;
            }
        }
    }
    // Vertical
    {
        double theta = M_PI/2;
        double cos_theta = cos(theta);
        double sin_theta = sin(theta);
        for(int j=0;j<N;j++) {
            projs[j].proj = x[j]*cos_theta + y[j]*sin_theta;
            projs[j].color = c[j];
        }
        qsort(projs, N, sizeof(PointProj), cmp_proj);
        int current_red =0;
        for(int j=0;j<N;j++) {
            if(projs[j].color == 'B'){
                current_red =0;
            }
            else{
                current_red++;
                if(current_red > max_red) max_red = current_red;
            }
        }
    }

    printf("%d\n", max_red);

    free(x);
    free(y);
    free(c);
    free(unique_angles);
    free(projs);
    return 0;
}
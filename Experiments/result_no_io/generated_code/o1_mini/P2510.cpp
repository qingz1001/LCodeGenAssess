#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXN 1000
#define MAX_INTERVALS 2000
#define PI 3.14159265358979323846

struct Circle {
    double r;
    double x;
    double y;
} circles[MAXN];

struct Interval {
    double start;
    double end;
} intervals[MAX_INTERVALS];

int cmp(const void* a, const void* b) {
    double diff = ((struct Interval*)a)->start - ((struct Interval*)b)->start;
    if (diff < -1e-12) return -1;
    if (diff > 1e-12) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%lf %lf %lf", &circles[i].r, &circles[i].x, &circles[i].y);
    }
    double total = 0.0;
    for(int i=0;i<n;i++){
        int m = 0;
        for(int j=i+1;j<n;j++){
            double dx = circles[j].x - circles[i].x;
            double dy = circles[j].y - circles[i].y;
            double d_sq = dx*dx + dy*dy;
            double d = sqrt(d_sq);
            if(d >= circles[i].r + circles[j].r - 1e-12){
                continue;
            }
            if(d <= fabs(circles[j].r - circles[i].r) + 1e-12){
                if(circles[j].r >= circles[i].r - 1e-12){
                    m = 1;
                    break;
                }
                else{
                    continue;
                }
            }
            double theta = atan2(dy, dx);
            if(theta < 0) theta += 2*PI;
            double cos_alpha = (circles[i].r*circles[i].r + d_sq - circles[j].r*circles[j].r)/(2.0 * circles[i].r * d);
            if(cos_alpha > 1.0) cos_alpha = 1.0;
            if(cos_alpha < -1.0) cos_alpha = -1.0;
            double alpha = acos(cos_alpha);
            double start = theta - alpha;
            double end = theta + alpha;
            if(start < 0){
                start += 2*PI;
                end += 2*PI;
            }
            if(end >= 2*PI){
                intervals[m].start = start;
                intervals[m].end = 2*PI;
                m++;
                intervals[m].start = 0.0;
                intervals[m].end = end - 2*PI;
                m++;
            }
            else{
                intervals[m].start = start;
                intervals[m].end = end;
                m++;
            }
        }
        if(m ==1 && intervals[0].start <=0.0 && intervals[0].end >=2*PI -1e-12){
            continue;
        }
        qsort(intervals, m, sizeof(struct Interval), cmp);
        double covered = 0.0;
        double current_start = -1.0, current_end = -1.0;
        for(int k=0;k<m;k++){
            if(current_end < 0){
                current_start = intervals[k].start;
                current_end = intervals[k].end;
            }
            else{
                if(intervals[k].start <= current_end + 1e-12){
                    if(intervals[k].end > current_end){
                        current_end = intervals[k].end;
                    }
                }
                else{
                    covered += current_end - current_start;
                    current_start = intervals[k].start;
                    current_end = intervals[k].end;
                }
            }
        }
        if(current_end > current_start){
            covered += current_end - current_start;
        }
        if(covered > 2*PI) covered = 2*PI;
        double visible = (2.0 * PI - covered) * circles[i].r;
        total += visible;
    }
    printf("%.3lf\n", total);
    return 0;
}
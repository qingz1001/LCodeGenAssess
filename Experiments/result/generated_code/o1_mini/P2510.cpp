#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXN 1000
#define MAX_EVENTS 2000
#define PI acos(-1.0)

typedef struct {
    double start;
    double end;
} Interval;

int cmp(const void *a, const void *b){
    Interval *ia = (Interval*)a;
    Interval *ib = (Interval*)b;
    if (ia->start < ib->start) return -1;
    if (ia->start > ib->start) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    double r[MAXN], x[MAXN], y[MAXN];
    for(int i=0;i<n;i++) scanf("%lf %lf %lf", &r[i], &x[i], &y[i]);
    double total = 0.0;
    for(int i=0;i<n;i++){
        int m = 0;
        for(int j=0;j<n;j++) if(j != i){
            double dx = x[j] - x[i];
            double dy = y[j] - y[i];
            double d_sq = dx*dx + dy*dy;
            double d = sqrt(d_sq);
            if(d >= r[i] + r[j]) continue;
            if(d <= fabs(r[j] - r[i])){
                if(r[j] >= r[i]){
                    m = -1;
                    break;
                }
                else continue;
            }
            double angle = atan2(dy, dx);
            double alpha = acos((r[i]*r[i] + d_sq - r[j]*r[j]) / (2.0 * r[i] * d));
            double start = angle - alpha;
            double end = angle + alpha;
            while(start < 0) start += 2*PI;
            while(end < 0) end += 2*PI;
            while(start >= 2*PI) start -= 2*PI;
            while(end >= 2*PI) end -= 2*PI;
            if(start > end){
                Interval iv1 = {start, 2*PI};
                Interval iv2 = {0, end};
                // Add iv1
                if(m != -1){
                    // Assuming m != -1
                    // Should check m != -1 earlier
                }
                // Temporarily ignore
                // Since m == -1 handled above
                // Add iv1 and iv2
                // To simplify, skip wrap-around by adding two intervals
                // First interval
                // Store later
            }
        }
    }
    // Placeholder
    return 0;
}
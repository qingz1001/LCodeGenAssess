#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_CHORDS 400000
#define PI 3.14159265358979323846

typedef struct {
    double start;
    double end;
} Interval;

int compare(const void *a, const void *b) {
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    if (ia->end < ib->end) return -1;
    if (ia->end > ib->end) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Interval *intervals = malloc(sizeof(Interval) * MAX_CHORDS);
    int cnt =0;
    for(int i=0;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        // Convert to angles
        double theta1 = ((a -1) * PI) / n;
        double theta2 = ((b -1) * PI) / n;
        if(theta1 > theta2){
            double tmp = theta1;
            theta1 = theta2;
            theta2 = tmp;
        }
        // Compute theta_p
        double theta_p = fmod((theta1 + theta2)/2.0 + PI/2.0, 2.0*PI);
        if(theta_p >= PI){
            theta_p -= PI;
        }
        // Compute start and end
        double start = theta_p - PI/2.0;
        if(start < 0){
            start += PI;
        }
        double end = theta_p + PI/2.0;
        if(end > PI){
            end -= PI;
        }
        if(start <= end){
            intervals[cnt].start = start;
            intervals[cnt].end = end;
            cnt++;
        }
        else{
            intervals[cnt].start = 0.0;
            intervals[cnt].end = end;
            cnt++;
            intervals[cnt].start = start;
            intervals[cnt].end = PI;
            cnt++;
        }
    }
    // Sort intervals by end
    qsort(intervals, cnt, sizeof(Interval), compare);
    // Greedy selection
    int answer =0;
    double last_covered = -1.0;
    for(int i=0;i<cnt;i++){
        if(intervals[i].start > last_covered +1e-12){
            answer++;
            last_covered = intervals[i].end;
        }
    }
    printf("%d\n", answer);
    free(intervals);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double p;
    double r;
    double d;
} Job;

int cmp_job(const void *a, const void *b){
    Job *ja = (Job*)a;
    Job *jb = (Job*)b;
    if (ja->d < jb->d) return -1;
    if (ja->d > jb->d) return 1;
    return 0;
}

int main(){
    int K;
    scanf("%d", &K);
    while(K--){
        int n, m;
        scanf("%d %d", &n, &m);
        Job jobs[n];
        for(int i=0;i<n;i++) scanf("%lf %lf %lf", &jobs[i].p, &jobs[i].r, &jobs[i].d);
        qsort(jobs, n, sizeof(Job), cmp_job);
        double s[m];
        for(int i=0;i<m;i++) scanf("%lf", &s[i]);
        double low = 0.0, high = 1e9, mid;
        for(int iter=0; iter < 100; iter++){
            mid = (low + high) / 2.0;
            // Assign jobs
            double available[m];
            for(int i=0;i<m;i++) available[i] = 0.0;
            int flag = 1;
            for(int i=0;i<n && flag; i++){
                double best_finish = 1e18;
                int sel = -1;
                for(int j=0; j<m; j++){
                    double start = (available[j] > jobs[i].r) ? available[j] : jobs[i].r;
                    double finish = start + jobs[i].p / s[j];
                    if(finish <= jobs[i].d + mid){
                        if(finish < best_finish){
                            best_finish = finish;
                            sel = j;
                        }
                    }
                }
                if(sel == -1){
                    flag = 0;
                }
                else{
                    available[sel] = best_finish;
                }
            }
            if(flag){
                high = mid;
            }
            else{
                low = mid;
            }
        }
        // To handle precision issues, round up a tiny bit
        printf("%.10lf\n", high);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int T;
    int S;
} Job;

int cmp(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    if (jobB->S != jobA->S)
        return jobB->S - jobA->S;
    else
        return jobA->T - jobB->T;
}

int main(){
    int N;
    scanf("%d", &N);
    Job jobs[N];
    int max_S = 0;
    for(int i=0;i<N;i++){
        scanf("%d %d", &jobs[i].T, &jobs[i].S);
        if(jobs[i].S > max_S)
            max_S = jobs[i].S;
    }
    qsort(jobs, N, sizeof(Job), cmp);
    long long current_time = max_S;
    for(int i=0;i<N;i++){
        if(current_time > jobs[i].S)
            current_time = jobs[i].S;
        current_time -= jobs[i].T;
        if(current_time < 0){
            printf("-1\n");
            return 0;
        }
    }
    printf("%lld\n", current_time);
}
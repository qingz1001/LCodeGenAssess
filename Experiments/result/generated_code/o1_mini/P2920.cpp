#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int T;
    int S;
} Job;

int cmp(const void* a, const void* b) {
    Job* jobA = (Job*)a;
    Job* jobB = (Job*)b;
    if (jobA->S != jobB->S)
        return jobA->S - jobB->S;
    return jobA->T - jobB->T;
}

int main(){
    int N;
    scanf("%d", &N);
    Job jobs[N];
    for(int i=0;i<N;i++) scanf("%d %d", &jobs[i].T, &jobs[i].S);
    qsort(jobs, N, sizeof(Job), cmp);
    long long end = jobs[N-1].S;
    for(int i=N-1;i>=0;i--){
        if(end > jobs[i].S) end = jobs[i].S;
        end -= jobs[i].T;
    }
    if(end < 0) printf("-1\n");
    else printf("%lld\n", end);
}
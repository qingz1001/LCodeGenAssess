#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t;
    int w;
} Job;

int compare(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    if (jobB->w != jobA->w)
        return jobB->w - jobA->w;
    else
        return jobA->t - jobB->t;
}

int parent[1001];

int find_set(int x){
    if(parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    Job jobs[500];
    for(int i=0;i<n;i++){
        scanf("%d", &jobs[i].t);
    }
    for(int i=0;i<n;i++){
        scanf("%d", &jobs[i].w);
    }
    qsort(jobs, n, sizeof(Job), compare);
    for(int i=0;i<=n;i++) parent[i]=i;
    long long sum_scheduled = 0;
    long long sum_all = 0;
    for(int i=0;i<n;i++) sum_all += jobs[i].w;
    for(int i=0;i<n;i++){
        int available = find_set(jobs[i].t);
        if(available >0){
            sum_scheduled += jobs[i].w;
            parent[available] = available-1;
        }
    }
    long long result = m - (sum_all - sum_scheduled);
    printf("%lld\n", result);
    return 0;
}
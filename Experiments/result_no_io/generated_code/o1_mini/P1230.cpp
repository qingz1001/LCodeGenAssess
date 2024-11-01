#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t;
    int w;
} Job;

int cmp(const void* a, const void* b){
    Job* ja = (Job*)a;
    Job* jb = (Job*)b;
    if(jb->w != ja->w) return jb->w - ja->w;
    return ja->t - jb->t;
}

int parent[1001];

int find_set(int x){
    if(parent[x] != x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

int main(){
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    Job jobs[500];
    for(int i=0;i<n;i++) scanf("%d", &jobs[i].t);
    for(int i=0;i<n;i++) scanf("%d", &jobs[i].w);
    qsort(jobs, n, sizeof(Job), cmp);
    for(int i=0;i<=n;i++) parent[i]=i;
    long long sum_scheduled=0;
    long long sum_total=0;
    for(int i=0;i<n;i++) sum_total += jobs[i].w;
    for(int i=0;i<n;i++){
        int available = find_set(jobs[i].t);
        if(available >0){
            sum_scheduled += jobs[i].w;
            parent[available] = available-1;
        }
    }
    long long result = m - (sum_total - sum_scheduled);
    printf("%lld\n", result);
}
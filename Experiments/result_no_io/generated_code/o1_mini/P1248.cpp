#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int A;
    int B;
} Job;

int compare(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    
    int groupA = jobA->A <= jobA->B ? 1 : 2;
    int groupB = jobB->A <= jobB->B ? 1 : 2;
    
    if (groupA != groupB) {
        return groupA - groupB;
    }
    
    if (groupA == 1) {
        if (jobA->A != jobB->A)
            return jobA->A - jobB->A;
        else
            return jobA->index - jobB->index;
    } else {
        if (jobA->B != jobB->B)
            return jobB->B - jobA->B;
        else
            return jobA->index - jobB->index;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    Job jobs[n];
    int A[n];
    int B[n];
    for(int i=0;i<n;i++) {
        scanf("%d", &A[i]);
    }
    for(int i=0;i<n;i++) {
        scanf("%d", &B[i]);
    }
    for(int i=0;i<n;i++) {
        jobs[i].index = i+1;
        jobs[i].A = A[i];
        jobs[i].B = B[i];
    }
    qsort(jobs, n, sizeof(Job), compare);
    long long timeA=0, timeB=0;
    for(int i=0;i<n;i++) {
        timeA += jobs[i].A;
        if(timeB < timeA){
            timeB = timeA;
        }
        timeB += jobs[i].B;
    }
    printf("%lld\n", timeB);
    for(int i=0;i<n;i++) {
        printf("%d%c", jobs[i].index, (i<n-1)?' ':'\n');
    }
    return 0;
}
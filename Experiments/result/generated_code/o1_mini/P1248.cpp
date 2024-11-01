#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int A;
    int B;
} Job;

int cmp_group1(const void *a, const void *b) {
    Job *ja = (Job *)a;
    Job *jb = (Job *)b;
    if (ja->A != jb->A)
        return ja->A - jb->A;
    return ja->index - jb->index;
}

int cmp_group2(const void *a, const void *b) {
    Job *ja = (Job *)a;
    Job *jb = (Job *)b;
    if (jb->B != ja->B)
        return jb->B - ja->B;
    return ja->index - jb->index;
}

int main(){
    int n;
    scanf("%d", &n);
    int *A = (int*)malloc(n * sizeof(int));
    int *B = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &A[i]);
    for(int i=0;i<n;i++) scanf("%d", &B[i]);
    Job *group1 = (Job*)malloc(n * sizeof(Job));
    Job *group2 = (Job*)malloc(n * sizeof(Job));
    int count1=0, count2=0;
    for(int i=0;i<n;i++){
        if(A[i] <= B[i]){
            group1[count1].index = i+1;
            group1[count1].A = A[i];
            group1[count1].B = B[i];
            count1++;
        }
        else{
            group2[count2].index = i+1;
            group2[count2].A = A[i];
            group2[count2].B = B[i];
            count2++;
        }
    }
    qsort(group1, count1, sizeof(Job), cmp_group1);
    qsort(group2, count2, sizeof(Job), cmp_group2);
    Job *schedule = (Job*)malloc(n * sizeof(Job));
    for(int i=0;i<count1;i++) schedule[i] = group1[i];
    for(int i=0;i<count2;i++) schedule[count1 + i] = group2[i];
    long long A_time=0, B_time=0;
    for(int i=0;i<n;i++){
        A_time += schedule[i].A;
        if(B_time < A_time) B_time = A_time;
        B_time += schedule[i].B;
    }
    printf("%lld\n", B_time);
    for(int i=0;i<n;i++) printf("%d%c", schedule[i].index, (i==n-1)?'\n':' ');
    free(A);
    free(B);
    free(group1);
    free(group2);
    free(schedule);
    return 0;
}
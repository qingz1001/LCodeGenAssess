#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int k;
    int s;
} Participant;

int cmp(const void *a, const void *b){
    Participant pa = *(Participant*)a;
    Participant pb = *(Participant*)b;
    if(pa.s != pb.s){
        return pb.s - pa.s;
    }
    return pa.k - pb.k;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Participant *p = malloc(n * sizeof(Participant));
    for(int i=0;i<n;i++) {
        scanf("%d %d", &p[i].k, &p[i].s);
    }
    qsort(p, n, sizeof(Participant), cmp);
    int threshold_idx = (int)(m * 1.5) -1;
    int threshold = p[threshold_idx].s;
    int count=0;
    for(int i=0;i<n;i++) {
        if(p[i].s >= threshold){
            count++;
        }
    }
    printf("%d %d\n", threshold, count);
    for(int i=0;i<n;i++) {
        if(p[i].s >= threshold){
            printf("%d %d\n", p[i].k, p[i].s);
        }
    }
    free(p);
    return 0;
}
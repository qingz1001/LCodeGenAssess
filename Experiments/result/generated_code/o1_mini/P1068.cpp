#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int k;
    int s;
} Candidate;

int compare(const void *a, const void *b) {
    Candidate *c1 = (Candidate*)a;
    Candidate *c2 = (Candidate*)b;
    if (c2->s != c1->s)
        return c2->s - c1->s;
    else
        return c1->k - c2->k;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Candidate arr[5000];
    for(int i=0;i<n;i++){
        scanf("%d %d", &arr[i].k, &arr[i].s);
    }
    qsort(arr, n, sizeof(Candidate), compare);
    int pos = (m * 3) / 2;
    if(m * 3 < 2 * pos){
        pos = pos;
    }
    int cutoff = arr[pos-1].s;
    int count =0;
    for(int i=0;i<n;i++){
        if(arr[i].s >= cutoff){
            count++;
        }
    }
    printf("%d %d\n", cutoff, count);
    for(int i=0;i<n;i++){
        if(arr[i].s >= cutoff){
            printf("%d %d\n", arr[i].k, arr[i].s);
        }
    }
    return 0;
}
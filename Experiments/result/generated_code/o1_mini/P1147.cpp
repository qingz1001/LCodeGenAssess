#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    long long start;
    long long end;
} Sequence;

int compare(const void *a, const void *b) {
    Sequence *sa = (Sequence *)a;
    Sequence *sb = (Sequence *)b;
    if (sa->start < sb->start) return -1;
    if (sa->start > sb->start) return 1;
    return 0;
}

int main(){
    long long M;
    scanf("%lld", &M);
    double sqrt_val = sqrt(8.0 * M +1);
    long long k_max = (long long)((sqrt_val -1)/2);
    Sequence seqs[2000];
    int count =0;
    for(long long k=2; k<=k_max; k++){
        if((2*M) % k !=0) continue;
        double temp = (double)(2*M)/k - (k-1);
        if(temp <=0) continue;
        if(floor(temp/2) != temp/2) continue;
        long long n = (long long)(temp/2);
        if(n >=1){
            seqs[count].start = n;
            seqs[count].end = n +k -1;
            count++;
        }
    }
    qsort(seqs, count, sizeof(Sequence), compare);
    for(int i=0;i<count;i++){
        printf("%lld %lld\n", seqs[i].start, seqs[i].end);
    }
    return 0;
}
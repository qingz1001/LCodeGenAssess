#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long a;
    long b;
} Sequence;

int compare(const void *p1, const void *p2) {
    Sequence *s1 = (Sequence *)p1;
    Sequence *s2 = (Sequence *)p2;
    if (s1->a < s2->a) return -1;
    if (s1->a > s2->a) return 1;
    return 0;
}

int main(){
    long M;
    scanf("%ld", &M);
    long max_n = (long)(floor( ( -1.0 + sqrt(1.0 + 8.0 * M)) / 2.0 ));
    Sequence *seq = (Sequence*)malloc(sizeof(Sequence) * (max_n));
    long count =0;
    for(long n=2; n<=max_n; n++){
        long numerator = M - (n*(n-1))/2;
        if(numerator <=0) continue;
        if(numerator % n ==0){
            long a = numerator / n;
            if(a >=1){
                seq[count].a = a;
                seq[count].b = a + n -1;
                count++;
            }
        }
    }
    qsort(seq, count, sizeof(Sequence), compare);
    for(long i=0;i<count;i++){
        printf("%ld %ld\n", seq[i].a, seq[i].b);
    }
    free(seq);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int cmp_asc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int cmp_desc(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int main(){
    int m, s, c;
    scanf("%d %d %d", &m, &s, &c);
    int barns[200];
    for(int i=0;i<c;i++) scanf("%d", &barns[i]);
    qsort(barns, c, sizeof(int), cmp_asc);
    if(m >= c){
        printf("%d\n", c);
        return 0;
    }
    int gaps[199];
    for(int i=1;i<c;i++) gaps[i-1] = barns[i] - barns[i-1] -1;
    qsort(gaps, c-1, sizeof(int), cmp_desc);
    int total = barns[c-1] - barns[0] +1;
    for(int i=0;i<m-1 && i<c-1;i++) total -= gaps[i];
    printf("%d\n", total);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    long long x = *((long long*)a);
    long long y = *((long long*)b);
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int n;
    long long dist;
    scanf("%d %lld", &n, &dist);
    long long *p = (long long*)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++) scanf("%lld", &p[i]);
    qsort(p, n, sizeof(long long), cmp);
    int kept = 1;
    long long last = p[0];
    for(int i=1;i<n;i++){
        if(p[i] > last + dist){
            kept++;
            last = p[i-1];
        }
    }
    if(last < p[n-1]){
        kept++;
    }
    printf("%d\n", n - kept);
    free(p);
    return 0;
}
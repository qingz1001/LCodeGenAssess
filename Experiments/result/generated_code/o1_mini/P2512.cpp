#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    long long la = *(long long*)a;
    long long lb = *(long long*)b;
    if (la < lb) return -1;
    else if (la > lb) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    long long *a = (long long*)malloc(n * sizeof(long long));
    long long sum=0;
    for(int i=0;i<n;i++){
        scanf("%lld", &a[i]);
        sum +=a[i];
    }
    long long m = sum / n;
    long long *s = (long long*)malloc(n * sizeof(long long));
    long long cumulative=0;
    for(int i=0;i<n;i++){
        cumulative += a[i] - m;
        s[i] = cumulative;
    }
    qsort(s, n, sizeof(long long), compare);
    long long median = s[n/2];
    long long total=0;
    for(int i=0;i<n;i++) total += llabs(s[i] - median);
    printf("%lld\n", total);
    free(a);
    free(s);
    return 0;
}
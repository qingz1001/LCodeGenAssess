#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    int T[n];
    for(int i=0;i<n;i++) scanf("%d", &T[i]);
    qsort(T, n, sizeof(int), compare);
    long long total=0;
    long long current=0;
    for(int i=0;i<n;i++){
        current += T[i];
        total += current;
    }
    for(int i=0;i<n;i++) printf("%d%c", T[i], i<n-1?' ':'\n');
    double avg = (double)total / n;
    printf("%.2lf\n", avg);
    return 0;
}
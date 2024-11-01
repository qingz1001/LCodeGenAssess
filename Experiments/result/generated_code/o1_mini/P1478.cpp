#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int n;
    long long s;
    scanf("%d %lld", &n, &s);
    int a, b;
    scanf("%d %d", &a, &b);
    int *y = (int*)malloc(n * sizeof(int));
    int reachable = 0;
    for(int i=0;i<n;i++){
        int x, yi;
        scanf("%d %d", &x, &yi);
        if(x <= b || x <= a + b){
            y[reachable++] = yi;
        }
    }
    qsort(y, reachable, sizeof(int), cmp);
    int count=0;
    long long sum=0;
    for(int i=0;i<reachable;i++){
        if(sum + y[i] > s) break;
        sum += y[i];
        count++;
    }
    printf("%d\n", count);
    free(y);
    return 0;
}
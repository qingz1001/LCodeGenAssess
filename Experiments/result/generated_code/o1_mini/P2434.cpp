#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Interval;

int cmp(const void *x, const void *y){
    Interval *i1 = (Interval *)x;
    Interval *i2 = (Interval *)y;
    if(i1->a != i2->a)
        return i1->a - i2->a;
    return i1->b - i2->b;
}

int main(){
    int n;
    scanf("%d", &n);
    Interval *arr = (Interval *)malloc(n * sizeof(Interval));
    for(int i=0;i<n;i++) scanf("%d %d", &arr[i].a, &arr[i].b);
    qsort(arr, n, sizeof(Interval), cmp);
    Interval *merged = (Interval *)malloc(n * sizeof(Interval));
    int m =0;
    merged[m++] = arr[0];
    for(int i=1;i<n;i++){
        if(arr[i].a <= merged[m-1].b){
            if(arr[i].b > merged[m-1].b) merged[m-1].b = arr[i].b;
        }
        else{
            merged[m++] = arr[i];
        }
    }
    for(int i=0;i<m;i++) printf("%d %d\n", merged[i].a, merged[i].b);
    free(arr);
    free(merged);
    return 0;
}
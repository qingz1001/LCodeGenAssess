#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Interval;

int cmp(const void *x, const void *y) {
    Interval *i1 = (Interval *)x;
    Interval *i2 = (Interval *)y;
    if (i1->a != i2->a)
        return i1->a - i2->a;
    return i1->b - i2->b;
}

int main(){
    int n;
    scanf("%d", &n);
    Interval *arr = (Interval *)malloc(n * sizeof(Interval));
    for(int i=0;i<n;i++) {
        scanf("%d %d", &arr[i].a, &arr[i].b);
    }
    qsort(arr, n, sizeof(Interval), cmp);
    Interval *res = (Interval *)malloc(n * sizeof(Interval));
    int count =0;
    res[count++] = arr[0];
    for(int i=1;i<n;i++) {
        if(arr[i].a <= res[count-1].b){
            if(arr[i].b > res[count-1].b){
                res[count-1].b = arr[i].b;
            }
        }
        else{
            res[count++] = arr[i];
        }
    }
    for(int i=0;i<count;i++){
        printf("%d %d\n", res[i].a, res[i].b);
    }
    free(arr);
    free(res);
    return 0;
}
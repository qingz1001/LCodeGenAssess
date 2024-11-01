#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long value;
    int index;
} Bottle;

int cmp(const void *a, const void *b){
    if (((Bottle*)a)->value < ((Bottle*)b)->value) return -1;
    if (((Bottle*)a)->value > ((Bottle*)b)->value) return 1;
    return 0;
}

int binary_search_func(Bottle *arr, int n, long long target){
    int left = 0, right = n -1;
    while(left <= right){
        int mid = left + (right - left) /2;
        if(arr[mid].value == target){
            return arr[mid].index;
        }
        else if(arr[mid].value < target){
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Bottle *arr = (Bottle*)malloc(sizeof(Bottle)*n);
    for(int i=0;i<n;i++){
        scanf("%lld", &arr[i].value);
        arr[i].index = i+1;
    }
    qsort(arr, n, sizeof(Bottle), cmp);
    int Q;
    scanf("%d", &Q);
    while(Q--){
        long long m;
        scanf("%lld", &m);
        int res = binary_search_func(arr, n, m);
        printf("%d\n", res);
    }
    free(arr);
    return 0;
}
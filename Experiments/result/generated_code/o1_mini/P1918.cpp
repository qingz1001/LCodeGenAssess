#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int index;
} pos;

int cmp(const void* a, const void* b){
    int val_a = ((pos*)a)->a;
    int val_b = ((pos*)b)->a;
    if(val_a < val_b) return -1;
    else if(val_a > val_b) return 1;
    else return 0;
}

int binary_search_func(pos arr[], int n, int m){
    int left = 0, right = n -1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(arr[mid].a == m){
            return arr[mid].index;
        }
        else if(arr[mid].a < m){
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
    pos* arr = (pos*)malloc(sizeof(pos)*n);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i].a);
        arr[i].index = i+1;
    }
    qsort(arr, n, sizeof(pos), cmp);
    int Q;
    scanf("%d", &Q);
    while(Q--){
        int m;
        if(scanf("%d", &m)!=1){
            break;
        }
        int res = binary_search_func(arr, n, m);
        printf("%d\n", res);
    }
    free(arr);
    return 0;
}
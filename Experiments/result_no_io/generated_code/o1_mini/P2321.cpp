#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    
    int *tail = (int*)malloc(n * sizeof(int));
    int length = 0;
    
    for(int i=0;i<n;i++){
        int left = 0, right = length;
        while(left < right){
            int mid = left + (right - left)/2;
            if(tail[mid] < arr[i]) left = mid +1;
            else right = mid;
        }
        tail[left] = arr[i];
        if(left == length) length++;
    }
    
    printf("%d\n", length);
    free(arr);
    free(tail);
    return 0;
}
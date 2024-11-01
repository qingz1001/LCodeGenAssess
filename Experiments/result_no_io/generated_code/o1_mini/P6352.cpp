#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int nums[3];
    scanf("%d %d %d", &nums[0], &nums[1], &nums[2]);
    qsort(nums, 3, sizeof(int), cmp);
    int a = nums[0], b = nums[1], c = nums[2];
    int candidates[4];
    int count =0;
    // x1 = 2a - b
    candidates[count++] = 2*a - b;
    // x2 = 2c - b
    candidates[count++] = 2*c - b;
    // x3 = (a + b)/2 if a+b even
    if( (a + b) %2 ==0 ) candidates[count++] = (a + b)/2;
    // x4 = (b + c)/2 if b+c even
    if( (b + c) %2 ==0 ) candidates[count++] = (b + c)/2;
    for(int i=0;i<count;i++){
        int x = candidates[i];
        int arr[4] = {a, b, c, x};
        qsort(arr,4,sizeof(int), cmp);
        int d = arr[1] - arr[0];
        if( (arr[2] - arr[1] == d) && (arr[3] - arr[2] == d) ){
            printf("%d\n", x);
            return 0;
        }
    }
    return 0;
}
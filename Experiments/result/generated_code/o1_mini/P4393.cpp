#include <stdio.h>
#include <stdlib.h>

#define INF 2000000001

int main(){
    int n;
    scanf("%d", &n);
    long long *a = (long long *)malloc(n * sizeof(long long));
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    long long *stack = (long long *)malloc((n + 1) * sizeof(long long));
    int stack_top = 0;
    stack[stack_top++] = INF;
    long long sum = 0;
    for(int i = 0; i < n; i++){
        while(stack_top > 0 && stack[stack_top -1] <= a[i]){
            long long mid = stack[--stack_top];
            long long left = stack_top > 0 ? stack[stack_top -1] : INF;
            long long min_lr = left < a[i] ? left : a[i];
            sum += (mid > min_lr) ? mid : min_lr;
        }
        stack[stack_top++] = a[i];
    }
    while(stack_top >1){
        long long mid = stack[--stack_top];
        long long left = stack[stack_top -1];
        sum += (mid > left) ? mid : left;
    }
    printf("%lld\n", sum);
    free(a);
    free(stack);
    return 0;
}
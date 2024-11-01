#include <stdio.h>

#define MAXN 100000

long long a[MAXN + 1];
long long stack_arr[MAXN + 1];

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    
    int top = 0;
    stack_arr[0] = 0;
    long long count = 0;
    
    for(int i = 1; i <= n; i++){
        while(top > 0 && stack_arr[top] > a[i]) top--;
        if(stack_arr[top] < a[i]){
            stack_arr[++top] = a[i];
            count++;
        }
    }
    
    printf("%lld", count);
    return 0;
}
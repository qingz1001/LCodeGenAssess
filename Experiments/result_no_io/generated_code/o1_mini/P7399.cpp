#include <stdio.h>

#define MAX 100005

long long a[MAX];
long long stack_arr[MAX];
int top = 0;

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    
    stack_arr[top++] = 0;
    long long ans = 0;
    
    for(int i=1;i<=n;i++){
        if(a[i] > stack_arr[top-1]){
            stack_arr[top++] = a[i];
            ans++;
        }
        else{
            while(top > 0 && stack_arr[top-1] > a[i]){
                top--;
            }
            if(top == 0 || a[i] > stack_arr[top-1]){
                stack_arr[top++] = a[i];
                ans++;
            }
            // if a[i] == stack_arr[top-1], do nothing
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}
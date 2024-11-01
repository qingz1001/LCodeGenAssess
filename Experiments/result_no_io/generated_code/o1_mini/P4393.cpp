#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int n;
    scanf("%d", &n);
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;
    ll total=0;
    for(int i=0; i<n; i++){
        int a;
        scanf("%d", &a);
        while(top >=0 && stack[top] <= a){
            int last = stack[top--];
            if(top == -1){
                total += a;
            }
            else{
                if(a < stack[top]){
                    total += a;
                }
                else{
                    total += stack[top];
                }
            }
        }
        stack[++top] = a;
    }
    while(top >0){
        int last = stack[top--];
        total += stack[top];
    }
    printf("%lld\n", total);
    free(stack);
    return 0;
}
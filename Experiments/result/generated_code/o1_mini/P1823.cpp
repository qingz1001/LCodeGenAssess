#include<stdio.h>
#include<stdlib.h>

typedef long long ll;

typedef struct {
    int height;
    int count;
} StackElement;

int main(){
    int n;
    scanf("%d", &n);
    int* heights = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &heights[i]);
    
    StackElement* stack = (StackElement*)malloc(n * sizeof(StackElement));
    int top = -1;
    ll ans = 0;
    
    for(int i=0;i<n;i++){
        int current = heights[i];
        while(top >=0 && current >= stack[top].height){
            ans += stack[top].count;
            top--;
        }
        if(top >=0){
            if(current == stack[top].height){
                ans += stack[top].count;
                if(top-1 >=0){
                    ans +=1;
                }
                stack[top].count++;
            }
            else{
                ans +=1;
            }
        }
        else{
            // No action
        }
        if(top+1 < n){
            top++;
            stack[top].height = current;
            stack[top].count =1;
        }
    }
    printf("%lld", ans);
    free(heights);
    free(stack);
    return 0;
}
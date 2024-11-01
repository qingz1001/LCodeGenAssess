#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int height[n];
    for(int i=0;i<n;i++) scanf("%d", &height[i]);
    int stack[n];
    int top = -1;
    int count =0;
    for(int i=0;i<n;i++){
        while(top != -1 && height[i] > height[stack[top]]){
            int top_idx = stack[top--];
            if(top == -1) break;
            int distance = i - stack[top] -1;
            if(distance >0){
                int bounded_height = (height[i] < height[stack[top]] ? height[i] : height[stack[top]]) - height[top_idx];
                if(bounded_height >0){
                    count++;
                }
            }
        }
        stack[++top] = i;
    }
    printf("%d", count);
    return 0;
}
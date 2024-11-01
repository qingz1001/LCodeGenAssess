#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int count;
} StackElement;

int main(){
    int n;
    scanf("%d", &n);
    int *heights = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &heights[i]);
    
    StackElement *stack = (StackElement*)malloc(n * sizeof(StackElement));
    int top = -1;
    long long total = 0;
    
    for(int i=0;i<n;i++){
        int current = heights[i];
        int sameCount = 1;
        while(top >=0 && current >= stack[top].height){
            total += stack[top].count;
            if(current == stack[top].height){
                sameCount += stack[top].count;
            }
            top--;
        }
        if(top >=0){
            total +=1;
        }
        stack[++top].height = current;
        stack[top].count = sameCount;
    }
    printf("%lld\n", total);
    free(heights);
    free(stack);
    return 0;
}
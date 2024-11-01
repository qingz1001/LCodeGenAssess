#include <stdio.h>
#include <string.h>

int main(){
    char n[251];
    scanf("%s", n);
    int k;
    scanf("%d", &k);
    int len = strlen(n);
    char stack[251];
    int top = 0;
    for(int i=0;i<len;i++){
        while(k >0 && top >0 && stack[top-1] > n[i]){
            top--;
            k--;
        }
        stack[top++] = n[i];
    }
    while(k >0 && top >0){
        top--;
        k--;
    }
    // Remove leading zeros
    int start =0;
    while(start < top-1 && stack[start] == '0') start++;
    for(int i=start;i<top;i++) putchar(stack[i]);
    putchar('\n');
    return 0;
}
#include <stdio.h>
#include <string.h>

int main(){
    char n[251];
    int k;
    scanf("%s", n);
    scanf("%d", &k);
    int len = strlen(n);
    char stack[251];
    int top = 0;
    for(int i=0;i<len;i++){
        while(top >0 && k >0 && stack[top-1] > n[i]){
            top--;
            k--;
        }
        stack[top++] = n[i];
    }
    while(k >0){
        top--;
        k--;
    }
    int start=0;
    while(start < top-1 && stack[start] == '0') start++;
    for(int i=start;i<top;i++) printf("%c", stack[i]);
    printf("\n");
    return 0;
}
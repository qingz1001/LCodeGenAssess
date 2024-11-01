#include <stdio.h>
#include <string.h>

int main(){
    int M;
    char N[1005];
    scanf("%d %s", &M, N);
    int len = strlen(N);
    int first = 1;
    for(int i=0;i<len;i++){
        char c = N[i];
        if(c != '0'){
            if(!first){
                printf("+");
            }
            printf("%d*%d^%d", c - '0', M, len-1-i);
            first = 0;
        }
    }
    if(first){
        printf("0");
    }
    return 0;
}
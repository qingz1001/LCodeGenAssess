#include <stdio.h>
#include <string.h>

int main(){
    int M;
    char N[1002];
    scanf("%d %s", &M, N);
    int len = strlen(N);
    int first = 1;
    for(int i=0;i<len;i++){
        int digit = N[i]-'0';
        if(digit !=0){
            if(!first){
                printf("+");
            }
            printf("%d*%d^%d", digit, M, len-1-i);
            first = 0;
        }
    }
    printf("\n");
    return 0;
}
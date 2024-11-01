#include <stdio.h>

int main(){
    int a, b, c, d, e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    int sum = a + b + c + d + e;

    if(sum == 0){
        printf("Gray\n");
    }
    else if(sum <= 100){
        printf("Blue\n");
    }
    else if(sum <= 140){
        printf("Green\n");
    }
    else if(sum <= 259){
        printf("Orange\n");
    }
    else{
        printf("Red\n");
    }

    return 0;
}
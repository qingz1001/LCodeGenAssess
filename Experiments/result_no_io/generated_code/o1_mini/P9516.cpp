#include <stdio.h>

int main(){
    int a, b, c, d, e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    int sum = a + b + c + d + e;
    if(sum > 250){
        printf("Red\n");
    }
    else if(sum > 200){
        printf("Orange\n");
    }
    else if(sum > 100){
        printf("Green\n");
    }
    else if(sum > 0){
        printf("Blue\n");
    }
    else{
        printf("Gray\n");
    }
    return 0;
}
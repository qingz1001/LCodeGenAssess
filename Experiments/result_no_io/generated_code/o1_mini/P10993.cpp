#include <stdio.h>

int main(){
    unsigned int a;
    scanf("%u", &a);
    unsigned int product = 37 * a;
    if(product == 0){
        printf("Yes");
        return 0;
    }
    unsigned int first_digit = product % 10;
    product /=10;
    while(product >0){
        if((product %10)!=first_digit){
            printf("No");
            return 0;
        }
        product /=10;
    }
    printf("Yes");
    return 0;
}
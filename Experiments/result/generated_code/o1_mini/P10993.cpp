#include <stdio.h>

int main(){
    unsigned int a;
    scanf("%u", &a);
    unsigned long long product = 37ULL * a;
    if(product == 0){
        printf("Yes");
        return 0;
    }
    unsigned long long temp = product;
    int first_digit = temp % 10;
    temp /= 10;
    while(temp > 0){
        if(temp % 10 != first_digit){
            printf("No");
            return 0;
        }
        temp /= 10;
    }
    printf("Yes");
    return 0;
}
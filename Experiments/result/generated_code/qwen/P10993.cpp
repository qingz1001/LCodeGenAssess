#include <stdio.h>

int main() {
    int a, product;
    scanf("%d", &a);
    product = 37 * a;
    
    if (product == 0) {
        printf("Yes\n");
        return 0;
    }
    
    int first_digit = -1;
    while (product > 0) {
        int current_digit = product % 10;
        if (first_digit == -1) {
            first_digit = current_digit;
        } else if (current_digit != first_digit) {
            printf("No\n");
            return 0;
        }
        product /= 10;
    }
    
    printf("Yes\n");
    return 0;
}
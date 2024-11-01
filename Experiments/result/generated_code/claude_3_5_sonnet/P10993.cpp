#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    
    int product = 37 * a;
    int first_digit = product % 10;
    int is_equal = 1;
    
    while (product > 0) {
        if (product % 10 != first_digit) {
            is_equal = 0;
            break;
        }
        product /= 10;
    }
    
    if (is_equal) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}
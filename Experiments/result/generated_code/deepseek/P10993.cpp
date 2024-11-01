#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    int product = 37 * a;
    int firstDigit = product % 10;
    int temp = product;
    int allEqual = 1;

    while (temp > 0) {
        if (temp % 10 != firstDigit) {
            allEqual = 0;
            break;
        }
        temp /= 10;
    }

    if (allEqual) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}
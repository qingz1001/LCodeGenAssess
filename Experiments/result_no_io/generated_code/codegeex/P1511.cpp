#include <stdio.h>
#include <string.h>

#define MAX_LEN 200

int main() {
    char A[MAX_LEN + 1];
    scanf("%s", A);
    int lenA = strlen(A);

    int k = 0;
    int num = 1;
    int digit = 1;

    while (k < lenA) {
        if (A[k] - '0' < digit) {
            num++;
            digit = 1;
        } else if (A[k] - '0' == digit) {
            digit++;
        } else {
            num += A[k] - '0' - digit + 1;
            digit = 1;
        }

        if (num > 9) {
            num -= 10;
        }

        k++;
    }

    printf("%d\n", num);

    return 0;
}
#include <stdio.h>
#include <string.h>

void convertToDecimalExpression(int M, char *N) {
    int len = strlen(N);
    int first = 1;

    for (int i = 0; i < len; i++) {
        int digit = N[i] - '0';
        if (digit != 0) {
            if (!first) {
                printf("+");
            }
            printf("%d*%d^%d", digit, M, len - i - 1);
            first = 0;
        }
    }
    printf("\n");
}

int main() {
    int M;
    char N[1001];

    scanf("%d %s", &M, N);
    convertToDecimalExpression(M, N);

    return 0;
}
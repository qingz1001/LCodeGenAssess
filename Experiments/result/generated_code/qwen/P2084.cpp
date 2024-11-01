#include <stdio.h>
#include <string.h>

void printBinaryToDecimal(int M, char N[]) {
    int length = strlen(N);
    for (int i = 0; i < length; i++) {
        if (N[i] == '1') {
            printf("%d*%d^%d", 1, M, length - i - 1);
            if (i != length - 1) {
                printf("+");
            }
        }
    }
}

int main() {
    int M;
    char N[1001];
    scanf("%d %s", &M, N);
    printBinaryToDecimal(M, N);
    return 0;
}
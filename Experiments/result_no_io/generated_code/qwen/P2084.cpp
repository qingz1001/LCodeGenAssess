#include <stdio.h>
#include <string.h>

void printBinaryToDecimal(int M, int N) {
    char binary[1001];
    snprintf(binary, sizeof(binary), "%d", N);
    int length = strlen(binary);
    for (int i = 0; i < length; i++) {
        if (binary[i] != '0') {
            printf("%c*%d^%d", binary[i], M, length - i - 1);
            if (i + 1 < length) {
                printf("+");
            }
        }
    }
}

int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    printBinaryToDecimal(M, N);
    return 0;
}
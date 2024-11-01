#include <stdio.h>
#include <string.h>

int binaryToDecimal(char *binary) {
    int decimal = 0, base = 1;
    int len = strlen(binary);
    for (int i = len - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}

int ternaryToDecimal(char *ternary) {
    int decimal = 0, base = 1;
    int len = strlen(ternary);
    for (int i = len - 1; i >= 0; i--) {
        if (ternary[i] == '2') {
            decimal += 2 * base;
        } else if (ternary[i] == '1') {
            decimal += base;
        }
        base *= 3;
    }
    return decimal;
}

int main() {
    char binary[50], ternary[50];
    scanf("%s %s", binary, ternary);

    int binaryNum = binaryToDecimal(binary);
    int ternaryNum = ternaryToDecimal(ternary);

    int correctNum = 0;

    // Try flipping each bit in the binary representation
    for (int i = 0; i < strlen(binary); i++) {
        if (binary[i] == '0') {
            binary[i] = '1';
        } else {
            binary[i] = '0';
        }
        int newBinaryNum = binaryToDecimal(binary);
        if (newBinaryNum == ternaryNum) {
            correctNum = newBinaryNum;
            break;
        }
        binary[i] = binary[i] == '0' ? '1' : '0'; // Revert back
    }

    printf("%d\n", correctNum);

    return 0;
}
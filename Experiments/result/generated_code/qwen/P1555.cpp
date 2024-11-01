#include <stdio.h>
#include <string.h>

int binary_to_decimal(const char *binary) {
    int decimal = 0;
    for (int i = 0; binary[i] != '\0'; ++i) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal;
}

int ternary_to_decimal(const char *ternary) {
    int decimal = 0;
    for (int i = 0; ternary[i] != '\0'; ++i) {
        decimal = decimal * 3 + (ternary[i] - '0');
    }
    return decimal;
}

void correct_binary(char *binary, int expected_length) {
    for (int i = 0; i < expected_length; ++i) {
        if (binary[i] == '1') {
            binary[i] = '0';
            break;
        } else {
            binary[i] = '1';
        }
    }
}

void correct_ternary(char *ternary, int expected_length) {
    for (int i = 0; i < expected_length; ++i) {
        if (ternary[i] == '2') {
            ternary[i] = '1';
            break;
        } else {
            ternary[i] = '2';
        }
    }
}

int main() {
    char binary[10];
    char ternary[10];

    scanf("%s", binary);
    scanf("%s", ternary);

    int binary_length = strlen(binary);
    int ternary_length = strlen(ternary);

    correct_binary(binary, binary_length);
    correct_ternary(ternary, ternary_length);

    int decimal_from_binary = binary_to_decimal(binary);
    int decimal_from_ternary = ternary_to_decimal(ternary);

    printf("%d\n", decimal_from_binary);

    return 0;
}
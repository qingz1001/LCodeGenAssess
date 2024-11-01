#include <stdio.h>
#include <string.h>

int main() {
    char binary[32], ternary[32];
    scanf("%s %s", binary, ternary);

    int binary_len = strlen(binary);
    int ternary_len = strlen(ternary);

    int error_index = -1;
    for (int i = 0; i < binary_len; i++) {
        if (binary[i] != ternary[i / 2]) {
            if (error_index != -1) {
                error_index = -1;
                break;
            }
            error_index = i;
        }
    }

    if (error_index == -1) {
        for (int i = 0; i < ternary_len; i++) {
            if (ternary[i] != binary[i * 2]) {
                if (error_index != -1) {
                    error_index = -1;
                    break;
                }
                error_index = i * 2;
            }
        }
    }

    if (error_index != -1) {
        if (binary[error_index] == '0') {
            binary[error_index] = '1';
        } else {
            binary[error_index] = '0';
        }
    }

    int decimal_value = 0;
    for (int i = 0; i < binary_len; i++) {
        decimal_value = decimal_value * 2 + (binary[i] - '0');
    }

    printf("%d\n", decimal_value);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>

// 将二进制字符串转换为十进制数
long long binary_to_decimal(char *binary) {
    long long decimal = 0;
    int len = strlen(binary);
    for (int i = 0; i < len; i++) {
        decimal += (binary[i] - '0') * pow(2, len - 1 - i);
    }
    return decimal;
}

// 将三进制字符串转换为十进制数
long long ternary_to_decimal(char *ternary) {
    long long decimal = 0;
    int len = strlen(ternary);
    for (int i = 0; i < len; i++) {
        decimal += (ternary[i] - '0') * pow(3, len - 1 - i);
    }
    return decimal;
}

int main() {
    char binary[32], ternary[32];
    scanf("%s", binary);
    scanf("%s", ternary);

    int len_bin = strlen(binary);
    int len_ter = strlen(ternary);

    // 生成所有可能的二进制数
    for (int i = 0; i < len_bin; i++) {
        char temp_binary[32];
        strcpy(temp_binary, binary);
        temp_binary[i] = (binary[i] == '0') ? '1' : '0';
        long long dec_bin = binary_to_decimal(temp_binary);

        // 生成所有可能的三进制数
        for (int j = 0; j < len_ter; j++) {
            for (char k = '0'; k <= '2'; k++) {
                if (ternary[j] != k) {
                    char temp_ternary[32];
                    strcpy(temp_ternary, ternary);
                    temp_ternary[j] = k;
                    long long dec_ter = ternary_to_decimal(temp_ternary);

                    // 检查是否匹配
                    if (dec_bin == dec_ter) {
                        printf("%lld\n", dec_bin);
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}
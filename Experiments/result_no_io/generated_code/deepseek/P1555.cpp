#include <stdio.h>
#include <string.h>
#include <math.h>

// 将二进制字符串转换为十进制数
long long binary_to_decimal(char *binary) {
    long long decimal = 0;
    int len = strlen(binary);
    for (int i = 0; i < len; i++) {
        decimal += (binary[i] - '0') * pow(2, len - i - 1);
    }
    return decimal;
}

// 将三进制字符串转换为十进制数
long long ternary_to_decimal(char *ternary) {
    long long decimal = 0;
    int len = strlen(ternary);
    for (int i = 0; i < len; i++) {
        decimal += (ternary[i] - '0') * pow(3, len - i - 1);
    }
    return decimal;
}

int main() {
    char binary[32], ternary[32];
    scanf("%s", binary);
    scanf("%s", ternary);

    int binary_len = strlen(binary);
    int ternary_len = strlen(ternary);

    // 尝试修改二进制字符串中的每一位
    for (int i = 0; i < binary_len; i++) {
        char original_bit = binary[i];
        for (char new_bit = '0'; new_bit <= '1'; new_bit++) {
            if (new_bit != original_bit) {
                binary[i] = new_bit;
                long long decimal_from_binary = binary_to_decimal(binary);

                // 尝试修改三进制字符串中的每一位
                for (int j = 0; j < ternary_len; j++) {
                    char original_ternary_bit = ternary[j];
                    for (char new_ternary_bit = '0'; new_ternary_bit <= '2'; new_ternary_bit++) {
                        if (new_ternary_bit != original_ternary_bit) {
                            ternary[j] = new_ternary_bit;
                            long long decimal_from_ternary = ternary_to_decimal(ternary);

                            // 如果两个十进制数相等，则找到了正确的 N
                            if (decimal_from_binary == decimal_from_ternary) {
                                printf("%lld\n", decimal_from_binary);
                                return 0;
                            }
                        }
                    }
                    ternary[j] = original_ternary_bit; // 恢复原始值
                }
            }
        }
        binary[i] = original_bit; // 恢复原始值
    }

    return 0;
}
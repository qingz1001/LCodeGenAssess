#include <stdio.h>
#include <string.h>

int main() {
    char input[2005];
    scanf("%s", input);

    int len = strlen(input);
    int sign = 1; // 用于记录当前数字的符号，1表示正数，-1表示负数
    int num = 0;  // 用于存储当前数字
    int result = 0; // 用于存储最终结果

    for (int i = 0; i < len; i++) {
        if (input[i] == '+') {
            sign = 1;
        } else if (input[i] == '-') {
            sign = -1;
        } else if (input[i] >= '0' && input[i] <= '9') {
            num = num * 10 + (input[i] - '0');
        } else if (input[i] == '(') {
            int j = i + 1;
            while (input[j] != ')') {
                num = num * 10 + (input[j] - '0');
                j++;
            }
            i = j;
        } else if (input[i] == ')') {
            // do nothing
        } else if (input[i] == '*') {
            int j = i + 1;
            int multiplier = 0;
            while (input[j] >= '0' && input[j] <= '9') {
                multiplier = multiplier * 10 + (input[j] - '0');
                j++;
            }
            num *= multiplier;
            i = j - 1;
        } else if (input[i] == ' ') {
            // do nothing
        } else {
            printf("Invalid input\n");
            return 0;
        }
        result += sign * num;
        num = 0;
    }

    printf("%d\n", result);
    return 0;
}
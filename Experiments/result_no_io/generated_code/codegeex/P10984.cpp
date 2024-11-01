#include <stdio.h>

int main() {
    // 七段码状态码
    int codes[18][7] = {
        {0, 0, 0, 1, 1, 1, 1}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 0, 0, 1, 1, 0, 1}, // 2
        {1, 0, 0, 1, 0, 1, 1}, // 3
        {0, 1, 0, 1, 0, 0, 1}, // 4
        {1, 1, 0, 0, 0, 1, 1}, // 5
        {1, 1, 0, 0, 1, 1, 1}, // 6
        {1, 0, 0, 0, 0, 1, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };

    // 输入的七段码状态码
    int input[18];
    for (int i = 0; i < 18; i++) {
        int code;
        scanf("%d", &code);
        for (int j = 0; j < 7; j++) {
            input[i] = (code >> j) & 1;
        }
    }

    // 计算可能的数字数量
    int count = 0;
    for (int i = 0; i < 1000000000; i++) {
        int num = i;
        int valid = 1;
        for (int j = 0; j < 18; j++) {
            int digit = num % 10;
            if (codes[digit][0] != input[j * 7 + 0] ||
                codes[digit][1] != input[j * 7 + 1] ||
                codes[digit][2] != input[j * 7 + 2] ||
                codes[digit][3] != input[j * 7 + 3] ||
                codes[digit][4] != input[j * 7 + 4] ||
                codes[digit][5] != input[j * 7 + 5] ||
                codes[digit][6] != input[j * 7 + 6]) {
                valid = 0;
                break;
            }
            num /= 10;
        }
        if (valid) {
            count++;
        }
    }

    // 输出结果
    printf("%d\n", count);
    return 0;
}
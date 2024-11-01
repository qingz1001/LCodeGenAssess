#include <stdio.h>
#include <string.h>

int main() {
    char keys[] = "5TGYHN6RYHBVC8IUK9OLJP0W";
    char input[51];
    int fingerCounts[8] = {0};

    // 读取输入字符串
    scanf("%s", input);

    // 遍历输入字符串，计算每根手指的按键次数
    for (int i = 0; i < strlen(input); i++) {
        for (int j = 0; j < 10; j++) {
            if (input[i] == keys[j * 2]) {
                fingerCounts[j]++;
                break;
            }
        }
    }

    // 输出每根手指的按键次数
    for (int i = 0; i < 8; i++) {
        printf("%d\n", fingerCounts[i]);
    }

    return 0;
}
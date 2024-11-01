#include <stdio.h>
#include <string.h>

int main() {
    char hexColor[8]; // 存储输入的十六进制颜色码
    scanf("%s", hexColor);

    // 初始化反色的RGB值
    int r = 0, g = 0, b = 0;

    // 提取并计算RGB值
    r = 16 * (hexColor[1] - '0') + (hexColor[2] - '0');
    g = 16 * (hexColor[3] - '0') + (hexColor[4] - '0');
    b = 16 * (hexColor[5] - '0') + (hexColor[6] - '0');

    // 计算反色的RGB值
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;

    // 转换反色的RGB值为十六进制
    char hexDigits[] = "0123456789ABCDEF";
    hexColor[1] = hexDigits[r / 16];
    hexColor[2] = hexDigits[r % 16];
    hexColor[3] = hexDigits[g / 16];
    hexColor[4] = hexDigits[g % 16];
    hexColor[5] = hexDigits[b / 16];
    hexColor[6] = hexDigits[b % 16];

    // 输出反色的十六进制颜色码
    printf("%s\n", hexColor);

    return 0;
}
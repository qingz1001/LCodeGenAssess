#include <stdio.h>
#include <string.h>

int main() {
    char color[8];
    scanf("%s", color);
    
    // 提取RGB值并转换为十进制
    int r = 16 * (color[1] - '0') + (color[2] - '0');
    int g = 16 * (color[3] - '0') + (color[4] - '0');
    int b = 16 * (color[5] - '0') + (color[6] - '0');
    
    // 计算反色
    int inv_r = 255 - r;
    int inv_g = 255 - g;
    int inv_b = 255 - b;
    
    // 将反色转换为十六进制并输出
    printf("#");
    printf("%02X%02X%02X\n", inv_r, inv_g, inv_b);
    
    return 0;
}
#include <stdio.h>
#include <string.h>

int main() {
    int M, N;
    char str[1001];
    
    // 读取输入的M和N
    scanf("%d %s", &M, str);
    
    int len = strlen(str);
    int first = 1; // 用于控制是否需要加号
    
    for (int i = 0; i < len; i++) {
        int digit = str[i] - '0'; // 将字符转换为整数
        
        // 如果系数不为0，则输出该项
        if (digit != 0) {
            if (!first) {
                printf("+"); // 如果不是第一项，则在前面加一个加号
            }
            printf("%d*%d^%d", digit, M, len - i - 1);
            first = 0; // 更新标志，表示已经输出过第一项
        }
    }
    
    return 0;
}
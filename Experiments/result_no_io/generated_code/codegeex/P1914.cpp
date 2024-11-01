#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char str[51];
    
    // 读取n
    scanf("%d", &n);
    // 读取字符串
    scanf("%s", str);
    
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            // 计算新的字符，注意循环从a开始
            str[i] = ((str[i] - 'a' + n) % 26) + 'a';
        }
    }
    
    // 输出结果
    printf("%s\n", str);
    
    return 0;
}
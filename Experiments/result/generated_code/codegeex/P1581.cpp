#include <stdio.h>
#include <string.h>

int main() {
    char s[1000];
    scanf("%s", s);
    
    int len = strlen(s);
    int i, j, k, carry, sum;
    int digits[1000] = {0}; // 存储每一位的数字
    int base[1000] = {0};  // 存储每一位的进制
    
    // 初始化进制数组
    for (i = 0; i < 1000; i++) {
        base[i] = 2;
    }
    
    // 解析输入字符串
    i = 0;
    while (s[i] != '+') {
        if (s[i] == ',') {
            base[i] = 2;
        } else {
            base[i] += s[i] - '0';
        }
        i++;
    }
    
    // 将第一个加数按进制解析并存储到digits数组
    i++;
    j = 0;
    while (s[i] != '+') {
        digits[j] = s[i] - '0';
        i++;
        j++;
    }
    
    // 将第二个加数按进制解析并存储到digits数组
    i++;
    j = 0;
    while (i < len) {
        digits[j] += s[i] - '0';
        i++;
        j++;
    }
    
    // 进位计算
    carry = 0;
    for (i = 0; i < 1000; i++) {
        sum = digits[i] + carry;
        digits[i] = sum % base[i];
        carry = sum / base[i];
    }
    
    // 输出结果
    for (i = 0; i < 1000; i++) {
        if (digits[i] > 0 || i == 0) {
            printf("%d", digits[i]);
        }
    }
    
    return 0;
}
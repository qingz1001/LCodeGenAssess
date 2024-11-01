#include <stdio.h>
#include <string.h>

int main() {
    int n, left = 0, right = 0;
    char s[1000005];

    // 读取输入
    scanf("%d", &n);
    scanf("%s", s);

    // 遍历字符串，统计左括号和右括号的数量
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }
    }

    // 最大匹配前缀长度为左右括号数量的最小值的两倍
    printf("%d\n", 2 * (left < right ? left : right));

    return 0;
}
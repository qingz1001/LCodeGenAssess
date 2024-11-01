#include <stdio.h>
#include <string.h>

#define MAX_LEN 5000001

int main() {
    int n;
    char s[MAX_LEN];
    char s1[MAX_LEN * 2];
    int i, j;

    // 读取输入
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%c", &s[i]);
    }

    // 将字符串复制一份，形成环
    for (i = 0; i < n; i++) {
        s1[i] = s[i];
        s1[i + n] = s[i];
    }

    // 查找字典序最小的字符串
    char min_str[MAX_LEN * 2];
    strncpy(min_str, s1, n);
    for (i = 1; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (s1[i + j] < min_str[j]) {
                strncpy(min_str, s1 + i, n);
                break;
            } else if (s1[i + j] > min_str[j]) {
                break;
            }
        }
    }

    // 找到字典序最小的字符串的第一个字符在原字符串中的位置
    for (i = 0; i < n; i++) {
        if (s[i] == min_str[0]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}
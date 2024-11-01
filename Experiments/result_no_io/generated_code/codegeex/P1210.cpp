#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 20000

int main() {
    char input[MAX_LEN];
    char clean[MAX_LEN];
    int len, i, j, maxLen = 0, maxIndex = -1;
    int palindrome[MAX_LEN];

    // 读取输入
    while (fgets(input, MAX_LEN, stdin) != NULL) {
        for (i = 0, j = 0; input[i] != '\0'; i++) {
            if (isalpha(input[i])) {
                clean[j++] = tolower(input[i]);
            }
        }
        clean[j] = '\0';
    }

    len = strlen(clean);

    // 预处理，计算每个位置作为中心的最长回文长度
    for (i = 0; i < len; i++) {
        int left = i, right = i, length = 0;

        // 向两边扩展，计算奇数长度的回文
        while (left >= 0 && right < len && clean[left] == clean[right]) {
            length += 2;
            left--;
            right++;
        }

        palindrome[i] = length;

        // 向两边扩展，计算偶数长度的回文
        left = i;
        right = i + 1;
        length = 1;

        while (left >= 0 && right < len && clean[left] == clean[right]) {
            length += 2;
            left--;
            right++;
        }

        if (length > palindrome[i]) {
            palindrome[i] = length;
        }
    }

    // 找到最长回文的长度和位置
    for (i = 0; i < len; i++) {
        if (palindrome[i] > maxLen) {
            maxLen = palindrome[i];
            maxIndex = i;
        }
    }

    // 输出最长回文的长度
    printf("%d\n", maxLen);

    // 输出最长回文的原文
    int start = maxIndex - (maxLen - 1) / 2;
    for (i = start; i < start + maxLen; i++) {
        printf("%c", input[i]);
    }

    return 0;
}
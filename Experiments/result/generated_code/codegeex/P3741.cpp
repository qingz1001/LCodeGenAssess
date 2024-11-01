#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char s[101];
    scanf("%d", &n);
    scanf("%s", s);

    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'V' && s[i + 1] == 'K') {
            count++;
        }
    }

    int max_count = count;

    // 尝试将一个字符改变为 'V' 或 'K'，计算最大可能的 VK 数量
    for (int i = 0; i < n; i++) {
        char original = s[i];
        if (s[i] == 'V') {
            s[i] = 'K';
        } else if (s[i] == 'K') {
            s[i] = 'V';
        } else {
            continue;
        }

        int new_count = 0;
        for (int j = 0; j < n - 1; j++) {
            if (s[j] == 'V' && s[j + 1] == 'K') {
                new_count++;
            }
        }

        max_count = (max_count > new_count) ? max_count : new_count;

        // 恢复原始字符
        s[i] = original;
    }

    printf("%d\n", max_count);
    return 0;
}
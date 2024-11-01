#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char s[101];
    scanf("%s", s);

    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'V' && s[i + 1] == 'K') {
            count++;
        }
    }

    // 检查是否可以通过改变一个字符来增加 VK 的数量
    int max_count = count;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'V') {
            // 尝试将 s[i] 改为 'K'，检查是否可以增加 VK 的数量
            int new_count = count;
            for (int j = i + 1; j < n; j++) {
                if (s[j] == 'K') {
                    new_count++;
                    break;
                }
            }
            if (new_count > max_count) {
                max_count = new_count;
            }
        } else if (s[i] == 'K') {
            // 尝试将 s[i] 改为 'V'，检查是否可以增加 VK 的数量
            int new_count = count;
            for (int j = i + 1; j < n; j++) {
                if (s[j] == 'V') {
                    new_count++;
                    break;
                }
            }
            if (new_count > max_count) {
                max_count = new_count;
            }
        }
    }

    printf("%d\n", max_count);
    return 0;
}
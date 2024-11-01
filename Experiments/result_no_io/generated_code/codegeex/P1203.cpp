#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char necklace[360];
    scanf("%d", &n);
    scanf("%s", necklace);

    // 扩展项链以处理环形结构
    for (int i = 0; i < n; i++) {
        necklace[n + i] = necklace[i];
    }

    int max_beads = 0;

    // 遍历所有可能的断点
    for (int i = 0; i < n; i++) {
        int left = i;
        int right = i + 1;
        int count = 0;

        // 向左收集珠子
        while (left >= 0 && (necklace[left] == necklace[i] || necklace[left] == 'w')) {
            count++;
            left--;
        }

        // 向右收集珠子
        while (right < 2 * n && (necklace[right] == necklace[i] || necklace[right] == 'w')) {
            count++;
            right++;
        }

        // 如果遇到不同的颜色，停止收集
        if (necklace[left] != necklace[i] && necklace[left] != 'w') {
            break;
        }

        if (count > max_beads) {
            max_beads = count;
        }
    }

    printf("%d\n", max_beads);
    return 0;
}
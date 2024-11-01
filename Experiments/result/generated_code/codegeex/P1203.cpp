#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int brokenNecklace(int n, char *s) {
    int maxCount = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        char color = 'x'; // 'x' 表示未初始化
        int j = i;
        // 向右收集珠子
        while (count < n && (s[j] == color || s[j] == 'w' || color == 'x')) {
            if (color == 'x') {
                color = s[j];
            }
            count++;
            j = (j + 1) % n;
        }
        j = i - 1;
        // 向左收集珠子
        while (count < n && (s[j] == color || s[j] == 'w' || color == 'x')) {
            if (color == 'x') {
                color = s[j];
            }
            count++;
            j = (j - 1 + n) % n;
        }
        maxCount = max(maxCount, count);
    }
    return maxCount;
}

int main() {
    int n;
    char s[351];
    scanf("%d", &n);
    scanf("%s", s);
    printf("%d\n", brokenNecklace(n, s));
    return 0;
}
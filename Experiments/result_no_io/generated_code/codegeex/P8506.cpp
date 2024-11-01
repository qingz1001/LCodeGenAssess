#include <stdio.h>
#include <string.h>

int main() {
    int n, count = 0;
    char line[101];

    // 读取行数
    scanf("%d\n", &n);

    // 逐行读取文本
    for (int i = 0; i < n; i++) {
        fgets(line, 101, stdin);
        int len = strlen(line);
        int spaceCount = 0;

        // 计算行首空格数
        for (int j = 0; j < len; j++) {
            if (line[j] == ' ') {
                spaceCount++;
            } else {
                break;
            }
        }

        // 判断是否为一级标题
        if (len > spaceCount && line[spaceCount] == '#') {
            bool isTitle = true;
            for (int j = spaceCount + 1; j < len; j++) {
                if (line[j] != ' ') {
                    isTitle = false;
                    break;
                }
            }
            if (isTitle) {
                count++;
            }
        }
    }

    // 输出一级标题个数
    printf("%d\n", count);

    return 0;
}
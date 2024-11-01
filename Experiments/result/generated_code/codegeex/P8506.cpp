#include <stdio.h>
#include <string.h>

int main() {
    int n, count = 0;
    char line[101];

    // 读取行数
    scanf("%d", &n);

    // 逐行读取文本
    for (int i = 0; i < n; i++) {
        scanf("%s", line);

        // 跳过空行
        if (strlen(line) == 0) continue;

        // 检查是否为一级标题
        int len = strlen(line);
        int sharp_count = 0;
        int space_count = 0;

        // 统计井号和空格数量
        for (int j = 0; j < len; j++) {
            if (line[j] == '#') {
                sharp_count++;
            } else if (line[j] == ' ') {
                space_count++;
            } else {
                // 非空白字符出现，跳出循环
                break;
            }
        }

        // 检查是否满足一级标题的条件
        if (sharp_count > 0 && space_count > 0 && sharp_count == space_count) {
            count++;
        }
    }

    // 输出一级标题个数
    printf("%d\n", count);

    return 0;
}
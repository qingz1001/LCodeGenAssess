#include <stdio.h>

int main() {
    int notes[8];
    int ascending = 1, descending = 1;

    // 读取输入的8个音符
    for (int i = 0; i < 8; i++) {
        scanf("%d", &notes[i]);
    }

    // 检查是否为升序
    for (int i = 0; i < 7; i++) {
        if (notes[i] + 1 != notes[i + 1]) {
            ascending = 0;
        }
    }

    // 检查是否为降序
    for (int i = 0; i < 7; i++) {
        if (notes[i] - 1 != notes[i + 1]) {
            descending = 0;
        }
    }

    // 根据检查结果输出
    if (ascending) {
        printf("ascending\n");
    } else if (descending) {
        printf("descending\n");
    } else {
        printf("mixed\n");
    }

    return 0;
}
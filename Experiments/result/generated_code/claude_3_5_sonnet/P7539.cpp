#include <stdio.h>

int main() {
    int notes[8];
    int ascending = 1, descending = 1;
    
    // 读取输入
    for (int i = 0; i < 8; i++) {
        scanf("%d", &notes[i]);
    }
    
    // 检查是否为升序或降序
    for (int i = 1; i < 8; i++) {
        if (notes[i] > notes[i-1]) {
            descending = 0;
        } else if (notes[i] < notes[i-1]) {
            ascending = 0;
        }
    }
    
    // 输出结果
    if (ascending) {
        printf("ascending\n");
    } else if (descending) {
        printf("descending\n");
    } else {
        printf("mixed\n");
    }
    
    return 0;
}
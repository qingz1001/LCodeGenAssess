#include <stdio.h>
#include <stdbool.h>

#define MAX_NUM 1000

int main() {
    int N, i, j, count = 0;
    int numbers[MAX_NUM + 1] = {0}; // 初始化所有数字的计数为0
    int unique_numbers[100]; // 存储去重后的数字

    // 读取输入的随机数个数
    scanf("%d", &N);

    // 读取随机数并统计每个数字出现的次数
    for (i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        numbers[num]++;
    }

    // 找出所有不重复的数字
    for (i = 1; i <= MAX_NUM; i++) {
        if (numbers[i] > 0) {
            unique_numbers[count++] = i;
        }
    }

    // 输出去重后的数字个数
    printf("%d\n", count);

    // 对不重复的数字进行排序
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (unique_numbers[j] > unique_numbers[j + 1]) {
                int temp = unique_numbers[j];
                unique_numbers[j] = unique_numbers[j + 1];
                unique_numbers[j + 1] = temp;
            }
        }
    }

    // 输出去重并排序后的数字
    for (i = 0; i < count; i++) {
        printf("%d ", unique_numbers[i]);
    }

    return 0;
}
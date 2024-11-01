#include <stdio.h>

int main() {
    int nums[3];
    char order[4];
    int temp;

    // 读取输入的三个数字
    for (int i = 0; i < 3; i++) {
        scanf("%d", &nums[i]);
    }

    // 读取输入的顺序
    scanf("%s", order);

    // 对数字进行排序
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (nums[i] > nums[j]) {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    // 根据顺序输出数字
    for (int i = 0; i < 3; i++) {
        if (order[i] == 'A') {
            printf("%d", nums[0]);
        } else if (order[i] == 'B') {
            printf("%d", nums[1]);
        } else if (order[i] == 'C') {
            printf("%d", nums[2]);
        }
        if (i < 2) {
            printf(" ");
        }
    }

    return 0;
}
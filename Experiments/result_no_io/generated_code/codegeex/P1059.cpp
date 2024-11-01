#include <stdio.h>

int main() {
    int n, m = 0;
    scanf("%d", &n);
    int numbers[1000] = {0}; // 用于记录1到1000的数字是否出现过

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        numbers[num] = 1; // 标记数字出现过
    }

    for (int i = 1; i <= 1000; i++) {
        if (numbers[i] == 1) { // 输出出现过且按顺序的数字
            printf("%d ", i);
            m++;
        }
    }

    printf("\n%d\n", m);

    return 0;
}
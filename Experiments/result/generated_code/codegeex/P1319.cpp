#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N); // 读取N值

    int count = 0; // 用于记录当前是第几个数字
    int currentBit = 0; // 用于记录当前是0还是1，0表示0，1表示1

    while (count < 2 * N - 1) {
        int num;
        scanf("%d", &num); // 读取连续的0或1的个数

        for (int i = 0; i < num; i++) {
            printf("%d", currentBit); // 输出当前是0还是1
        }

        currentBit = 1 - currentBit; // 切换0和1
        count++; // 计数器加1

        if (count % N == 0) {
            printf("\n"); // 每输出N个数字后换行
        }
    }

    return 0;
}
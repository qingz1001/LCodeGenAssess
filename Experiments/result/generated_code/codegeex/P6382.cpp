#include <stdio.h>

int main() {
    char plate[9];
    scanf("%s", plate);

    // 判断是否为本地车牌
    if (plate[0] != 'M' || plate[1] != 'D' || plate[2] != 'A') {
        // 外地车牌，工作日都限行
        printf("1 1 1 1 1\n");
    } else {
        // 本地车牌，根据尾号判断是否限行
        int tail_number = 0;
        int multiplier = 1;
        for (int i = 7; i >= 0; i--) {
            if (plate[i] >= '0' && plate[i] <= '9') {
                tail_number = tail_number + (plate[i] - '0') * multiplier;
                multiplier *= 10;
            }
        }
        // 取最后一位数字
        tail_number = tail_number % 10;

        int restrictions[5][2] = {{1, 9}, {2, 8}, {3, 7}, {4, 6}, {5, 0}};
        for (int i = 0; i < 5; i++) {
            if (tail_number == restrictions[i][0] || tail_number == restrictions[i][1]) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
    return 0;
}
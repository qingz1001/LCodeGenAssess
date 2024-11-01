#include <stdio.h>
#include <string.h>

int main() {
    char license_plate[9];
    scanf("%s", license_plate);

    // 判断是否为本地车牌
    if (license_plate[0] != 'M' || license_plate[1] != 'D' || license_plate[2] != 'A') {
        // 外地车牌，工作日均限行
        for (int i = 0; i < 5; i++) {
            printf("1 ");
        }
    } else {
        // 本地车牌，根据尾号判断限行情况
        int tail_number = -1;
        // 找到车牌号的尾号
        for (int i = 7; i >= 0; i--) {
            if (license_plate[i] >= '0' && license_plate[i] <= '9') {
                tail_number = license_plate[i] - '0';
                break;
            }
        }
        // 根据尾号判断限行情况
        for (int i = 0; i < 5; i++) {
            if ((i == 0 && (tail_number == 1 || tail_number == 9)) ||
                (i == 1 && (tail_number == 2 || tail_number == 8)) ||
                (i == 2 && (tail_number == 3 || tail_number == 7)) ||
                (i == 3 && (tail_number == 4 || tail_number == 6)) ||
                (i == 4 && (tail_number == 5 || tail_number == 0))) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
    }
    printf("\n");
    return 0;
}
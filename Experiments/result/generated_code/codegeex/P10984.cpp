#include <stdio.h>
#include <stdbool.h>

// 七段码的状态码
int codes[18] = {
    0b0000011, 0b1001011, 0b0000001, 0b0100001, 0b0101011,
    0b0110110, 0b1111111, 0b0010110, 0b0101001, 0b0010110,
    0b1011100, 0b0100110, 0b1010000, 0b0010011, 0b0001111,
    0b0101101, 0b0110101, 0b1101010
};

// 判断一个状态码是否有效
bool isValid(int code) {
    // 如果状态码为0或者为1111111（即数字为0或9），则无效
    if (code == 0 || code == 0b1111111) {
        return false;
    }
    // 如果状态码中存在两个相邻的1，则无效
    for (int i = 0; i < 7; i++) {
        if ((code & (1 << i)) && (code & (1 << (i + 1)))) {
            return false;
        }
    }
    return true;
}

int main() {
    int count = 0;
    // 遍历所有可能的18位状态码
    for (int i = 0; i < (1 << 18); i++) {
        int valid = true;
        for (int j = 0; j < 18; j++) {
            int segment = (i >> j) & 1;
            if (segment == 1 && !isValid(codes[j])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}
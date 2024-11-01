#include <stdio.h>
#include <string.h>

// 定义七段码状态码
const char* segments[10] = {
    "1111110", "0110000", "1101101", "1111001", "0110011",
    "1011011", "1011111", "1110000", "1111111", "1111011"
};

// 检查两个七段码是否匹配
int match(char* seg, char* target) {
    for (int i = 0; i < 7; i++) {
        if (target[i] == '1' && seg[i] == '0') {
            return 0;
        }
    }
    return 1;
}

int main() {
    // 输入的七段码状态码
    char input[18][8] = {
        "0000011", "1001011", "0000001", "0100001", "0101011", "0110110",
        "1111111", "0010110", "0101001", "0010110", "1011100", "0100110",
        "1010000", "0010011", "0001111", "0101101", "0110101", "1101010"
    };

    int count = 1;

    // 计算可能的数字组合数
    for (int i = 0; i < 18; i++) {
        int possible_count = 0;
        for (int j = 0; j < 10; j++) {
            if (match(segments[j], input[i])) {
                possible_count++;
            }
        }
        count *= possible_count;
    }

    printf("%d\n", count);

    return 0;
}
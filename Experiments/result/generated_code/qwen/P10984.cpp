#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 1000000000000000000ULL

int main() {
    unsigned long long codes[18] = {
        0b0000011, 0b1001011, 0b0000001, 0b0100001, 0b0101011, 0b0110110,
        0b1111111, 0b0010110,
        0b0101001, 0b0010110,
        0b1011100, 0b0100110,
        0b1010000, 0b0010011,
        0b0001111, 0b0101101,
        0b0110101, 0b1101010
    };

    unsigned long long count = 0;
    for (unsigned long long i = 0; i < MAX_NUM; ++i) {
        int valid = 1;
        for (int j = 0; j < 18; ++j) {
            if ((i >> (j * 7)) & 0x7F != codes[j]) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            ++count;
        }
    }

    printf("%llu\n", count);
    return 0;
}
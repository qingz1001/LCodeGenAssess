#include <stdio.h>
#include <string.h>

int main() {
    char ipv6[39];
    scanf("%s", ipv6);

    int i, j, k;
    int zero_count = 0, max_zero_count = 0, max_zero_start = 0;
    int colon_count = 0;

    // 找到最长的全零组
    for (i = 0; i < 8; i++) {
        if (ipv6[i * 5] == '0' && ipv6[i * 5 + 1] == '0' && ipv6[i * 5 + 2] == '0' && ipv6[i * 5 + 3] == '0') {
            for (j = i; j < 8; j++) {
                if (ipv6[j * 5] == '0' && ipv6[j * 5 + 1] == '0' && ipv6[j * 5 + 2] == '0' && ipv6[j * 5 + 3] == '0') {
                    zero_count += 4;
                } else {
                    break;
                }
            }
            if (zero_count > max_zero_count) {
                max_zero_count = zero_count;
                max_zero_start = i;
            }
            zero_count = 0;
            i = j - 1;
        }
    }

    // 输出压缩后的IPv6地址
    for (i = 0; i < 8; i++) {
        if (i == max_zero_start) {
            if (colon_count == 0) {
                printf("::");
                colon_count++;
            }
            i += max_zero_count - 1;
        } else {
            printf("%c%c%c%c:", ipv6[i * 5], ipv6[i * 5 + 1], ipv6[i * 5 + 2], ipv6[i * 5 + 3]);
        }
    }
    printf("\n");

    return 0;
}
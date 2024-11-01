#include <stdio.h>
#include <string.h>

// 函数用于计算 n 的 a 次幂的最后 k 位
void calculate_power(char* n, int a, int k, char* result) {
    int len = strlen(n);
    for (int i = 0; i < k; i++) {
        result[i] = '0';
    }
    result[k] = '\0';

    for (int i = 0; i < k; i++) {
        for (int j = len - 1; j >= 0; j--) {
            if (n[j] != '0') {
                int power = (n[j] - '0') * (a % 10);
                int carry = power / 10;
                int digit = power % 10;

                for (int l = k - 1; l >= 0; l--) {
                    if (l == i) {
                        result[l] = (result[l] - '0' + digit) % 10 + '0';
                    } else {
                        result[l] = (result[l] - '0' + carry * (l - i)) % 10 + '0';
                    }
                    carry = (result[l] - '0') / 10;
                    result[l] = (result[l] - '0') % 10 + '0';
                }
                break;
            }
        }
    }
}

int main() {
    char n[101];
    int k;
    scanf("%s %d", n, &k);

    char powers[101][101];
    int lengths[101];

    // 初始化 powers 和 lengths 数组
    for (int i = 0; i < 101; i++) {
        lengths[i] = -1;
        for (int j = 0; j < 101; j++) {
            powers[i][j] = '\0';
        }
    }

    // 计算 n 的 0 次幂
    char power[101];
    calculate_power(n, 1, k, power);
    strcpy(powers[0], power);
    lengths[0] = 1;

    // 计算 n 的 1 次幂
    calculate_power(n, 1, k, power);
    strcpy(powers[1], power);
    lengths[1] = 1;

    int found_cycle = 0;
    int cycle_length = 0;

    for (int i = 2; i < 101; i++) {
        calculate_power(n, i, k, power);
        strcpy(powers[i], power);
        lengths[i] = 1;

        for (int j = 0; j < i; j++) {
            if (strcmp(powers[i], powers[j]) == 0) {
                found_cycle = 1;
                cycle_length = i - j;
                break;
            }
        }

        if (found_cycle) {
            break;
        }
    }

    if (found_cycle) {
        printf("%d\n", cycle_length);
    } else {
        printf("-1\n");
    }

    return 0;
}
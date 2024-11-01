#include <stdio.h>
#include <string.h>

// 将字符串表示的大数转换为长整型数组，每个数组元素表示一个数字位
void str_to_long_array(char *str, long *arr, int *len) {
    int i, j;
    *len = strlen(str);
    for (i = 0; i < *len; i++) {
        arr[i] = str[*len - 1 - i] - '0';
    }
}

// 计算数组表示的大数乘以 n 的 k 次方
void multiply(long *arr, int len, int n, int k) {
    long carry = 0;
    for (int i = 0; i < len; i++) {
        arr[i] = arr[i] * n * (long)pow(10, k) + carry;
        carry = arr[i] / 10;
        arr[i] %= 10;
    }
    while (carry) {
        arr[len++] = carry % 10;
        carry /= 10;
    }
}

// 计算最少所需的砝码数
int min_coins(long *arr, int len, int n) {
    int coins = 0;
    for (int i = len - 1; i >= 0; i--) {
        coins += arr[i];
        if (coins >= n) {
            coins -= n;
        }
    }
    return coins;
}

int main() {
    char str[10001];
    long arr[10001];
    int m, n, len;

    // 输入重量 m 和底数 n
    scanf("%s", str);
    scanf("%d", &n);

    // 将字符串表示的大数转换为长整型数组
    str_to_long_array(str, arr, &len);

    int k = 0;
    while (1) {
        long temp[10001];
        memcpy(temp, arr, sizeof(long) * len);
        multiply(temp, len, n, k);
        if (temp[0] == 0 && temp[1] < n) {
            break;
        }
        k++;
    }

    // 计算最少所需的砝码数
    int coins = min_coins(arr, len, n);

    // 输出结果
    printf("%d\n", coins + k);

    return 0;
}
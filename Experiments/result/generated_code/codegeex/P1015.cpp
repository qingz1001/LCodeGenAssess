#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 将字符串表示的数字转换为整型数组，方便处理
void strToIntArray(char *str, int *arr, int base) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            arr[i] = str[i] - '0';
        } else {
            arr[i] = str[i] - 'A' + 10;
        }
    }
}

// 判断一个数是否是回文数
int isPalindrome(int *arr, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (arr[i] != arr[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

// 进行一次N进制的加法
void add(int *arr, int len, int base) {
    int carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        int sum = arr[i] + carry;
        if (i == len - 1) {
            sum += base - 1; // 加上进制的最大值
        }
        arr[i] = sum % base;
        carry = sum / base;
    }
}

int main() {
    int N;
    char M[101];
    scanf("%d\n%s", &N, M);

    int len = strlen(M);
    int *arr = (int *)malloc(len * sizeof(int));

    strToIntArray(M, arr, N);

    int step = 0;
    while (step <= 30) {
        if (isPalindrome(arr, len)) {
            printf("STEP=%d\n", step);
            free(arr);
            return 0;
        }
        add(arr, len, N);
        step++;
    }

    printf("Impossible!\n");
    free(arr);
    return 0;
}
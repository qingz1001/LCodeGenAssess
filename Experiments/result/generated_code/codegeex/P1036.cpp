#include <stdio.h>
#include <stdbool.h>

// 判断一个数是否为素数
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 0;
    // 组合数计算
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int m = j + 1; m < n; m++) {
                if (isPrime(arr[i] + arr[j] + arr[m])) {
                    count++;
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}
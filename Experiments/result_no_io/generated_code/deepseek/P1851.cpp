#include <stdio.h>
#include <stdbool.h>

int sum_of_divisors(int n) {
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int s;
    scanf("%d", &s);

    int limit = 18000; // 根据题目数据规模设定上限
    int divisors_sum[limit + 1];

    for (int i = 1; i <= limit; i++) {
        divisors_sum[i] = sum_of_divisors(i);
    }

    for (int a = s; a <= limit; a++) {
        int b = divisors_sum[a];
        if (b < a && divisors_sum[b] == a) {
            printf("%d %d\n", a, b);
            return 0;
        }
    }

    printf("No such pair found\n");
    return 0;
}
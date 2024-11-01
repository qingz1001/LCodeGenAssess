#include <stdio.h>

int sum_of_divisors(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int main() {
    int s;
    scanf("%d", &s);

    for (int a = s; ; a++) {
        int sum_a = sum_of_divisors(a);
        if (sum_a > a) continue; // 跳过不可能是好友的数
        if (sum_a != a) {
            int sum_sum_a = sum_of_divisors(sum_a);
            if (sum_sum_a == a) {
                printf("%d %d\n", a, sum_a);
                break;
            }
        }
    }

    return 0;
}
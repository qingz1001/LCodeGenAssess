#include <stdio.h>
#include <string.h>

int n;
int primes[1000000] = {0, 1, 1}; // 0 和 1 不是质数

// 判断一个数是否是质数
int is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

// 深度优先搜索生成特殊质数
void dfs(int len, int num) {
    if (len == n) {
        printf("%d\n", num);
        return;
    }
    int last_digit = num % 10;
    for (int i = 0; i < 10; i++) {
        if (i == 0 && last_digit == 0) continue; // 避免以0开头
        int new_num = num * 10 + i;
        if (primes[new_num]) {
            dfs(len + 1, new_num);
        }
    }
}

int main() {
    scanf("%d", &n);
    if (n == 1) {
        printf("2\n3\n5\n7\n");
        return 0;
    }
    // 预处理所有长度为n-1的特殊质数
    for (int i = 10; i < 1000000; i++) {
        if (is_prime(i)) {
            primes[i] = 1;
        }
    }
    // 从所有以2, 3, 5, 7开头的质数开始深度优先搜索
    dfs(1, 2);
    dfs(1, 3);
    dfs(1, 5);
    dfs(1, 7);
    return 0;
}
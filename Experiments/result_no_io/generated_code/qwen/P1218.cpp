#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void find_special_primes(int n) {
    int digits[8];
    bool visited[1000000] = {false};
    for (int i = 1; i < 10; i++) {
        digits[0] = i;
        visited[i] = true;
        for (int len = 1; len < n; len++) {
            for (int j = 1; j < 10; j++) {
                int next_num = digits[len] * 10 + j;
                if (!visited[next_num] && is_prime(next_num)) {
                    digits[len + 1] = j;
                    visited[next_num] = true;
                }
            }
        }
    }

    for (int i = 0; i < 1000000; i++) {
        if (visited[i] && is_prime(i)) {
            int temp = i;
            int count = 0;
            while (temp > 0) {
                count++;
                temp /= 10;
            }
            if (count == n) {
                printf("%d\n", i);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    find_special_primes(n);
    return 0;
}
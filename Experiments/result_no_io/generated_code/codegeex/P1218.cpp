#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void generate_superprime(int n, int current_length, int current_number) {
    if (current_length == n) {
        printf("%d\n", current_number);
        return;
    }
    for (int i = 1; i <= 9; i++) {
        int next_number = current_number * 10 + i;
        if (is_prime(next_number)) {
            generate_superprime(n, current_length + 1, next_number);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    if (n == 1) {
        printf("2\n3\n5\n7\n");
    } else {
        generate_superprime(n, 1, 2);
        generate_superprime(n, 1, 3);
        generate_superprime(n, 1, 5);
        generate_superprime(n, 1, 7);
    }
    return 0;
}
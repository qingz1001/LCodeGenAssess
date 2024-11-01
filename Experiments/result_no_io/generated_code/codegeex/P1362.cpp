#include <stdio.h>

int sum_of_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int is_rabbit_number(int x) {
    int sum_x = sum_of_digits(x);
    int sum_x_squared = sum_of_digits(x * x);
    return sum_x_squared == sum_x * sum_x;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);

    int count = 0;
    for (int i = L; i <= R; i++) {
        if (is_rabbit_number(i)) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
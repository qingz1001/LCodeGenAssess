#include <stdio.h>

void print_power_of_two(int n) {
    if (n == 0) {
        printf("0");
        return;
    }

    int first = 1;
    for (int i = 14; i >= 0; i--) { // 2^14 is the largest power of 2 less than 20000
        if (n & (1 << i)) {
            if (!first) {
                printf("+");
            }
            first = 0;
            printf("2");
            if (i > 1) {
                printf("(");
                print_power_of_two(i);
                printf(")");
            } else if (i == 1) {
                printf(""); // 2^1 is just 2
            } else {
                printf("(0)"); // 2^0 is 2(0)
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    print_power_of_two(n);
    return 0;
}
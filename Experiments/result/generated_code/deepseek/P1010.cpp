#include <stdio.h>

void print_power_of_two(int n) {
    if (n == 0) {
        printf("0");
        return;
    }

    int first = 1;
    for (int i = 30; i >= 0; i--) {
        if (n & (1 << i)) {
            if (!first) {
                printf("+");
            }
            first = 0;
            printf("2");
            if (i != 1) {
                printf("(");
                print_power_of_two(i);
                printf(")");
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
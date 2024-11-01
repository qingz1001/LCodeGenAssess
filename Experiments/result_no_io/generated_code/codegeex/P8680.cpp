#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int sum = 0;

    for (int i = 1; i <= n; i++) {
        int num = i;
        while (num > 0) {
            if (num % 10 == 2 || num % 10 == 0 || num % 10 == 1 || num % 10 == 9) {
                sum += i;
                break;
            }
            num /= 10;
        }
    }

    printf("%d\n", sum);
    return 0;
}
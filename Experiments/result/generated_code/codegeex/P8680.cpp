#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    int sum = 0;

    for (int i = 1; i <= n; i++) {
        int temp = i;
        int flag = 0;
        while (temp > 0) {
            int digit = temp % 10;
            if (digit == 2 || digit == 0 || digit == 1 || digit == 9) {
                flag = 1;
                break;
            }
            temp /= 10;
        }
        if (flag) {
            sum += i;
        }
    }

    printf("%d\n", sum);
    return 0;
}
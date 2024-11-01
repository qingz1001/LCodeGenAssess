#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int result = 1;
    int count2 = 0, count5 = 0;

    for (int i = 1; i <= N; i++) {
        int num = i;
        while (num % 2 == 0) {
            num /= 2;
            count2++;
        }
        while (num % 5 == 0) {
            num /= 5;
            count5++;
        }
        result = (result * num) % 10;
    }

    int diff = count2 - count5;
    for (int i = 0; i < diff; i++) {
        result = (result * 2) % 10;
    }

    printf("%d\n", result);
    return 0;
}
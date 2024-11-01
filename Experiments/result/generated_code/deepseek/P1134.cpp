#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int result = 1;
    int twoCount = 0;
    int fiveCount = 0;

    for (int i = 1; i <= N; i++) {
        int num = i;
        while (num % 2 == 0) {
            twoCount++;
            num /= 2;
        }
        while (num % 5 == 0) {
            fiveCount++;
            num /= 5;
        }
        result = (result * num) % 10;
    }

    int diff = twoCount - fiveCount;
    for (int i = 0; i < diff; i++) {
        result = (result * 2) % 10;
    }

    printf("%d\n", result);
    return 0;
}
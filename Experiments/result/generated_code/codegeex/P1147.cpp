#include <stdio.h>

int main() {
    int M;
    scanf("%d", &M);

    int sum = 0, start = 1;
    for (int i = 1; i <= M / 2; i++) {
        sum += i;
        if (sum == M) {
            printf("%d %d\n", start, i);
        } else if (sum > M) {
            break;
        }
        start++;
    }

    return 0;
}
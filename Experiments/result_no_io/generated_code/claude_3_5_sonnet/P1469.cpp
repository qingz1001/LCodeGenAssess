#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int result = 0;
    int temp;

    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        result ^= temp;
    }

    printf("%d\n", result);

    return 0;
}
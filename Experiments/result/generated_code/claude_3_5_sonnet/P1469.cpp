#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int result = 0;
    int length;

    for (int i = 0; i < n; i++) {
        scanf("%d", &length);
        result ^= length;
    }

    printf("%d\n", result);

    return 0;
}
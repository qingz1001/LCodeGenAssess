#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n * m % 3 != 0) {
        printf("0\n");
        return 0;
    }

    int result = (n * m) / 3;
    printf("%d\n", result);

    return 0;
}
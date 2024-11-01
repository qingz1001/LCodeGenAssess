#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n == m) {
        printf("0\n");
        return 0;
    }

    int result = n;
    for (int i = 1; i <= n / 2; i++) {
        result = (result > n - i) ? n - i : result;
    }

    printf("%d\n", result);
    return 0;
}
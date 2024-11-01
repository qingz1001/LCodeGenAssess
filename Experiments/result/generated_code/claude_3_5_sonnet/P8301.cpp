#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int main() {
    int n;
    scanf("%d", &n);

    char a[MAX_N + 1], b[MAX_N + 1];
    scanf("%s", a);
    scanf("%s", b);

    int count_a = 0, count_b = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == '1') count_a++;
        if (b[i] == '1') count_b++;
    }

    int result = abs(count_a - count_b);
    printf("%d\n", result);

    return 0;
}
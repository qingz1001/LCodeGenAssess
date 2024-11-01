#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char a[n + 1], b[n + 1], c[n + 1], d[n + 1];
    scanf("%s%s%s%s", a, b, c, d);

    for (int i = 0; i < n; i++) {
        if (a[i] > c[i]) {
            char temp = a[i];
            a[i] = c[i];
            c[i] = temp;

            temp = b[i];
            b[i] = d[i];
            d[i] = temp;
        }
    }

    printf("%s\n", b);

    return 0;
}
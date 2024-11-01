#include <stdio.h>
#include <string.h>

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int n;
    scanf("%d", &n);
    char a[n + 1], b[n + 1], c[n + 1], d[n + 1];
    scanf("%s%s%s%s", a, b, c, d);

    for (int i = 0; i < n; i++) {
        if (a[i] > c[i]) {
            swap(&a[i], &c[i]);
            swap(&b[i], &d[i]);
        }
    }

    printf("%s\n", b);

    return 0;
}
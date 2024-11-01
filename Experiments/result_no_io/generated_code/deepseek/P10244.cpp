#include <stdio.h>
#include <string.h>

void minimizeString(char *a, char *b, char *c, char *d, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] > c[i] || (a[i] == c[i] && b[i] > d[i])) {
            char temp = a[i];
            a[i] = c[i];
            c[i] = temp;

            temp = b[i];
            b[i] = d[i];
            d[i] = temp;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    char a[n+1], b[n+1], c[n+1], d[n+1];
    scanf("%s", a);
    scanf("%s", b);
    scanf("%s", c);
    scanf("%s", d);

    minimizeString(a, b, c, d, n);

    printf("%s\n", b);

    return 0;
}
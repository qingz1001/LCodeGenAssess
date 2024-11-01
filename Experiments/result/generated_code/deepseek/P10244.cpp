#include <stdio.h>
#include <string.h>

#define MAXN 100005

char a[MAXN], b[MAXN], c[MAXN], d[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", a);
    scanf("%s", b);
    scanf("%s", c);
    scanf("%s", d);

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

    printf("%s\n", b);
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_N 100005

char a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
char result[MAX_N];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s%s%s%s", a, b, c, d);

    for (int i = 0; i < n; i++) {
        if (a[i] < c[i] || (a[i] == c[i] && b[i] <= d[i])) {
            result[i] = b[i];
        } else {
            result[i] = d[i];
        }
    }
    result[n] = '\0';

    printf("%s\n", result);

    return 0;
}
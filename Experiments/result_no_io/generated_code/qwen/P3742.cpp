#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char x[101], y[101];
    scanf("%s %s", x, y);

    char z[101];
    for (int i = 0; i < n; i++) {
        if (x[i] == y[i]) {
            z[i] = x[i];
        } else {
            if (x[i] > y[i]) {
                z[i] = y[i];
            } else {
                z[i] = x[i];
            }
        }
    }

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (z[i] != x[i] && z[i] != y[i]) {
            printf("-1\n");
            return 0;
        }
        if (z[i] == x[i] || z[i] == y[i]) {
            found = 1;
        }
    }

    if (!found) {
        printf("-1\n");
        return 0;
    }

    z[n] = '\0';
    printf("%s\n", z);

    return 0;
}
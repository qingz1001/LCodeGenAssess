#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n], b[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    int flips = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            flips++;
        }
    }

    printf("%d\n", flips);

    return 0;
}
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int p[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int count = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[i - 1]) {
            p[i] += p[i - 1];
            for (int j = i - 1; j > 0; j--) {
                p[j] = p[j - 1] + p[j];
            }
            n--;
            i--;
        }
    }

    printf("%d\n", n - 1);
    return 0;
}
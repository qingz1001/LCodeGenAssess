#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[101];
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    int avg = sum / n;
    int moves = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            a[i] -= avg;
            a[i + 1] += avg;
        } else if (i == n) {
            a[i] -= avg;
            a[i - 1] += avg;
        } else {
            a[i] -= avg;
            a[i + 1] += avg;
            a[i - 1] += avg;
        }
        moves += abs(a[i]);
    }
    printf("%d\n", moves);
    return 0;
}
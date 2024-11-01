#include <stdio.h>

int main() {
    int n, A, B, C, a[10000000];
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    for (int i = 2; i <= n; i++)
        a[i] = ((long long) a[i - 1] * A + B) % 100000001;
    for (int i = 1; i <= n; i++)
        a[i] = a[i] % C + 1;

    double expected_correct = 0.0;
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            if (a[i] == 1 || a[i] == a[1]) {
                expected_correct += 1.0 / a[i];
            }
        } else {
            if (a[i] == a[i + 1]) {
                expected_correct += 1.0 / a[i];
            }
        }
    }

    printf("%.3lf\n", expected_correct);
    return 0;
}
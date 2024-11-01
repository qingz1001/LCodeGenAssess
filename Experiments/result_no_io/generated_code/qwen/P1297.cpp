#include <stdio.h>
#include <stdlib.h>

#define MOD 100000001

int main() {
    int n, A, B, C;
    scanf("%d%d%d%d", &n, &A, &B, &C);

    // Generate the sequence a
    int* a = (int*)malloc((n + 1) * sizeof(int));
    a[1] = 0;
    for (int i = 2; i <= n; i++) {
        a[i] = ((long long)a[i - 1] * A + B) % MOD;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = (a[i] % C) + 1;
    }

    // Calculate the expected number of correct answers
    double expected = 0.0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            expected += 1.0 / n;
        }
    }

    printf("%.3f\n", expected);

    free(a);
    return 0;
}
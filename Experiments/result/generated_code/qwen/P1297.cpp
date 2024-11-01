#include <stdio.h>
#include <stdlib.h>

#define MOD 100000001

int main() {
    int n, A, B, C, a[10000001];
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);

    double expected_correct = 0;

    for (int i = 1; i <= n; i++) {
        a[i] %= C;
        if (a[i] == 0) a[i] += C;
    }

    for (int i = 1; i <= n; i++) {
        int correct_count = 0;
        int current = i;
        for (int j = 0; j < n; j++) {
            if (current == 1 && a[current] == 1) correct_count++;
            current = (current + a[current] - 2) % n + 1;
        }
        expected_correct += correct_count / (double)n;
    }

    printf("%.3f\n", expected_correct);

    return 0;
}
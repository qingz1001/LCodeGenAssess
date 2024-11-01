#include <stdio.h>

int main() {
    int n, A, B, C;
    int a[10000001];
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    
    for (int i = 2; i <= n; i++) {
        a[i] = ((long long) a[i - 1] * A + B) % 100000001;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = a[i] % C + 1;
    }

    double expected_correct = 0.0;
    for (int i = 1; i <= n; i++) {
        int next_i = i % n + 1;
        expected_correct += 1.0 / (a[i] > a[next_i] ? a[i] : a[next_i]);
    }

    printf("%.3f\n", expected_correct);
    return 0;
}
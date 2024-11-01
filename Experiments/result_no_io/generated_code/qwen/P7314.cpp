#include <stdio.h>
#include <limits.h>

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int min_value = INT_MAX;

    for (int i = 0; i < N; i++) {
        int max_val = A[i];
        int min_val = A[i];
        for (int j = i + 1; j < N; j++) {
            if (A[j] > max_val) {
                max_val = A[j];
            }
            if (A[j] < min_val) {
                min_val = A[j];
            }
            int interval_value = max_val - min_val;
            if (interval_value < min_value) {
                min_value = interval_value;
            }
        }
    }

    printf("%d\n", min_value);

    return 0;
}
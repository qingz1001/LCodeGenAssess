#include <stdio.h>
#include <limits.h>

int main() {
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int min_val = INT_MAX;
    for (int L = 0; L < N; L++) {
        int max_in_interval = INT_MIN;
        int min_in_interval = INT_MAX;
        for (int R = L; R < N; R++) {
            if (A[R] > max_in_interval) {
                max_in_interval = A[R];
            }
            if (A[R] < min_in_interval) {
                min_in_interval = A[R];
            }
            int interval_value = max_in_interval - min_in_interval;
            if (interval_value < min_val) {
                min_val = interval_value;
            }
        }
    }

    printf("%d\n", min_val);

    return 0;
}
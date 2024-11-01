#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int *s = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
    }

    int max_value = s[0];
    for (int i = 1; i < N; i++) {
        if (s[i] > max_value) {
            max_value = s[i];
        }
    }

    int K = 1;
    while (1) {
        int *count = (int *)calloc(K, sizeof(int));
        int valid = 1;
        for (int i = 0; i < N; i++) {
            count[s[i] % K]++;
            if (count[s[i] % K] > 1) {
                valid = 0;
                break;
            }
        }
        free(count);
        if (valid) {
            printf("%d\n", K);
            break;
        }
        K++;
    }

    free(s);
    return 0;
}
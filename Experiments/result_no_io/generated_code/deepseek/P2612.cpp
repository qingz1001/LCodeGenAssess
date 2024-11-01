#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    int *a = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
    }

    int total_permutations = 0;
    int valid_permutations = 0;

    srand(time(NULL));

    for (int i = 0; i < 1000000; i++) {
        for (int j = N - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            int temp = a[j];
            a[j] = a[k];
            a[k] = temp;
        }

        int L = 0;
        for (int j = 0; j < N - 1; j++) {
            L += abs(a[j + 1] - a[j]);
        }

        if (L >= M) {
            valid_permutations++;
        }
        total_permutations++;
    }

    double probability = (double)valid_permutations / total_permutations;
    printf("%.*f\n", K, probability);

    free(a);
    return 0;
}
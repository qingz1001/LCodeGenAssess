#include <stdio.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int findPosition(int N, int K) {
    char **numbers = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        numbers[i] = (char *)malloc(11 * sizeof(char));
        sprintf(numbers[i], "%d", i + 1);
    }

    qsort(numbers, N, sizeof(char *), compare);

    int position = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(numbers[i], "K") == 0) {
            position = i + 1;
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        free(numbers[i]);
    }
    free(numbers);

    return position;
}

int main() {
    int K, M;
    scanf("%d %d", &K, &M);

    int N = 1;
    while (N <= 1000000000) {
        int position = findPosition(N, K);
        if (position == M) {
            printf("%d\n", N);
            return 0;
        }
        N++;
    }

    printf("0\n");
    return 0;
}
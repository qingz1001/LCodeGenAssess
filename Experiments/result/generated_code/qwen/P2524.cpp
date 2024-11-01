#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int count_permutations(int* arr, int n, int k) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int smaller = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] < arr[i]) smaller++;
        }
        count += smaller * factorial(n - i - 1);
        for (int j = i + 1; j < n; j++) {
            if (arr[j] == arr[i]) {
                for (int l = j; l > i; l--) {
                    arr[l] = arr[l - 1];
                }
                break;
            }
        }
    }
    return count + 1;
}

int main() {
    int N, X;
    scanf("%d %d", &N, &X);

    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        arr[i] = X % 10;
        X /= 10;
    }

    printf("%d\n", count_permutations(arr, N, X));

    free(arr);
    return 0;
}
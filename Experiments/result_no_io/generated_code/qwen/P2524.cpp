#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int count_permutations(int arr[], int start, int end) {
    if (start == end) return 1;
    int count = 0;
    for (int i = start; i <= end; i++) {
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;

        count += count_permutations(arr, start + 1, end);

        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
    }
    return count;
}

int main() {
    int N;
    scanf("%d", &N);
    char X[10];
    scanf("%s", X);

    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = X[i] - '0';
    }

    int rank = count_permutations(arr, 0, N - 1) + 1;
    printf("%d\n", rank);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int N, M, K;
int count = 0;
int total = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *arr, int l, int r) {
    if (l == r) {
        int L = 0;
        for (int i = 1; i < N; i++) {
            L += abs(arr[i] - arr[i - 1]);
        }
        if (L >= M) {
            count++;
        }
        total++;
    } else {
        for (int i = l; i <= r; i++) {
            swap((arr + l), (arr + i));
            permute(arr, l + 1, r);
            swap((arr + l), (arr + i)); // backtrack
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &K);
    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }
    permute(arr, 0, N - 1);
    double probability = (double)count / total;
    printf("%.*f\n", K, probability);
    return 0;
}
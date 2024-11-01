#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // Find the position to insert M
    int pos = -1;
    for (int i = 0; i < N - 1; i++) {
        if (arr[i] <= M && arr[i + 1] > M) {
            pos = i + 1;
            break;
        }
    }
    if (pos == -1) {
        pos = N;
    }

    // Insert M into the array
    for (int i = N; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = M;

    // Print the result
    for (int i = 0; i < N; i++) {
        printf("%d", arr[i]);
        if (i < N - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(arr);
    return 0;
}
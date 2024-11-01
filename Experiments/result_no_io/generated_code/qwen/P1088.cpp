#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Find the position of M in the array
    int pos = -1;
    for (int i = 0; i < N; i++) {
        if (arr[i] == M) {
            pos = i;
            break;
        }
    }
    
    // If M is not found, it means M is greater than all elements in the array
    if (pos == -1) {
        pos = N - 1;
    }
    
    // Rotate the array to the right by pos positions
    int temp = arr[pos];
    for (int i = pos; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = temp;
    
    // Print the new arrangement
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    free(arr);
    return 0;
}
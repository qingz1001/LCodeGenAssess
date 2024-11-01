#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_T 7

int is_arithmetic_sequence(int *arr, int len) {
    if (len < 3) return 0;
    for (int i = 1; i < len - 1; i++) {
        if (arr[i + 1] - arr[i] != arr[1] - arr[0]) return 0;
    }
    return 1;
}

void solve(int T, int **arrays, int *sizes) {
    for (int t = 0; t < T; t++) {
        int N = sizes[t];
        int *A = arrays[t];
        
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                for (int k = j + 1; k < N; k++) {
                    for (int l = k + 1; l < N; l++) {
                        int *subseq = (int *)malloc(4 * sizeof(int));
                        subseq[0] = A[i];
                        subseq[1] = A[j];
                        subseq[2] = A[k];
                        subseq[3] = A[l];
                        
                        if (is_arithmetic_sequence(subseq, 4)) {
                            printf("Y\n");
                            free(subseq);
                            goto next_test;
                        }
                        
                        free(subseq);
                    }
                }
            }
        }
        
        printf("N\n");
        
next_test:;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    
    int **arrays = (int **)malloc(T * sizeof(int *));
    int *sizes = (int *)malloc(T * sizeof(int));
    
    for (int t = 0; t < T; t++) {
        int N;
        scanf("%d", &N);
        sizes[t] = N;
        arrays[t] = (int *)malloc(N * sizeof(int));
        
        for (int i = 0; i < N; i++) {
            scanf("%d", &arrays[t][i]);
        }
    }
    
    solve(T, arrays, sizes);
    
    for (int t = 0; t < T; t++) {
        free(arrays[t]);
    }
    free(arrays);
    free(sizes);
    
    return 0;
}
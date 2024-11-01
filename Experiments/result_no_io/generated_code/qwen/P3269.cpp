#include <stdio.h>
#include <string.h>

#define MAX_N 4
#define MAX_LEN 10005

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve(char *A, int N, char *B[], int *minans, int *maxans) {
    int len_A = strlen(A);
    int len_B[MAX_N];
    for (int i = 0; i < N; i++) {
        len_B[i] = strlen(B[i]);
    }

    // Calculate the maximum coverage
    *maxans = 0;
    for (int i = 0; i <= len_A - len_B[0]; i++) {
        if (strncmp(A + i, B[0], len_B[0]) == 0) {
            int cover = len_B[0];
            for (int j = 1; j < N; j++) {
                int found = 0;
                for (int k = i; k <= len_A - len_B[j]; k++) {
                    if (strncmp(A + k, B[j], len_B[j]) == 0) {
                        cover += len_B[j];
                        i = k + len_B[j] - 1;
                        found = 1;
                        break;
                    }
                }
                if (!found) break;
            }
            *maxans = max(*maxans, cover);
        }
    }

    // Calculate the minimum coverage
    *minans = len_A;
    for (int i = 0; i <= len_A - len_B[0]; i++) {
        if (strncmp(A + i, B[0], len_B[0]) == 0) {
            int cover = len_B[0];
            for (int j = 1; j < N; j++) {
                int found = 0;
                for (int k = i; k <= len_A - len_B[j]; k++) {
                    if (strncmp(A + k, B[j], len_B[j]) == 0) {
                        cover += len_B[j];
                        i = k + len_B[j] - 1;
                        found = 1;
                        break;
                    }
                }
                if (!found) break;
            }
            *minans = min(*minans, len_A - cover);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char A[MAX_LEN];
        scanf("%s", A);
        int N;
        scanf("%d", &N);
        char *B[MAX_N];
        for (int i = 0; i < N; i++) {
            B[i] = (char *)malloc(MAX_LEN * sizeof(char));
            scanf("%s", B[i]);
        }

        int minans, maxans;
        solve(A, N, B, &minans, &maxans);

        printf("%d %d\n", minans, maxans);

        for (int i = 0; i < N; i++) {
            free(B[i]);
        }
    }
    return 0;
}
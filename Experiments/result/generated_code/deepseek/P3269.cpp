#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 10001

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void findMinMaxCoverage(char *A, char **B, int N, int *minAns, int *maxAns) {
    int lenA = strlen(A);
    int lenB[N];
    int pos[N][2];
    bool covered[lenA];
    memset(covered, false, sizeof(covered));

    for (int i = 0; i < N; i++) {
        lenB[i] = strlen(B[i]);
        pos[i][0] = -1;
        pos[i][1] = -1;
    }

    // Find all positions of each substring in A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= lenA - lenB[i]; j++) {
            if (strncmp(A + j, B[i], lenB[i]) == 0) {
                if (pos[i][0] == -1) {
                    pos[i][0] = j;
                }
                pos[i][1] = j;
            }
        }
    }

    // Calculate minimum coverage
    for (int i = 0; i < N; i++) {
        for (int j = pos[i][0]; j <= pos[i][1]; j++) {
            covered[j] = true;
        }
    }
    *minAns = 0;
    for (int i = 0; i < lenA; i++) {
        if (covered[i]) {
            (*minAns)++;
        }
    }

    // Calculate maximum coverage
    *maxAns = 0;
    for (int i = 0; i < N; i++) {
        *maxAns += lenB[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (pos[i][1] >= pos[j][0] && pos[i][0] <= pos[j][1]) {
                *maxAns -= min(pos[i][1] - pos[j][0] + 1, pos[j][1] - pos[i][0] + 1);
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char A[MAX_LEN];
        int N;
        scanf("%s", A);
        scanf("%d", &N);
        char *B[N];
        for (int i = 0; i < N; i++) {
            B[i] = (char *)malloc(MAX_LEN * sizeof(char));
            scanf("%s", B[i]);
        }

        int minAns, maxAns;
        findMinMaxCoverage(A, B, N, &minAns, &maxAns);
        printf("%d %d\n", minAns, maxAns);

        for (int i = 0; i < N; i++) {
            free(B[i]);
        }
    }
    return 0;
}
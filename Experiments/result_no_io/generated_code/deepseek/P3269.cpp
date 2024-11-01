#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10000
#define MAX_N 4

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int find_min_coverage(char *A, char *B[], int N) {
    int lenA = strlen(A);
    int min_coverage = lenA;

    for (int i = 0; i < N; i++) {
        int lenB = strlen(B[i]);
        int count = 0;
        for (int j = 0; j < lenA; j++) {
            if (strncmp(A + j, B[i], lenB) == 0) {
                count++;
                j += lenB - 1;
            }
        }
        min_coverage = min(min_coverage, lenA - count * (lenB - 1));
    }

    return min_coverage;
}

int find_max_coverage(char *A, char *B[], int N) {
    int lenA = strlen(A);
    int max_coverage = 0;

    for (int i = 0; i < N; i++) {
        int lenB = strlen(B[i]);
        int count = 0;
        for (int j = 0; j < lenA; j++) {
            if (strncmp(A + j, B[i], lenB) == 0) {
                count++;
                j += lenB - 1;
            }
        }
        max_coverage = max(max_coverage, count * lenB);
    }

    return max_coverage;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        char A[MAX_LEN + 1];
        int N;
        char B[MAX_N][MAX_LEN + 1];

        scanf("%s", A);
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%s", B[i]);
        }

        int min_ans = find_min_coverage(A, B, N);
        int max_ans = find_max_coverage(A, B, N);

        printf("%d %d\n", min_ans, max_ans);
    }

    return 0;
}
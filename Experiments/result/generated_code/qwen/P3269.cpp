#include <stdio.h>
#include <string.h>

#define MAX_LEN 10005
#define MAX_SUBSTR 5

int min_coverage(char *A, int N, char substr[MAX_SUBSTR][MAX_LEN]) {
    int len = strlen(A);
    int min_cover = len;
    for (int i = 0; i <= len - N; i++) {
        int cover = 0;
        int j = 0;
        while (j < N) {
            int k = 0;
            while (k < strlen(substr[j]) && A[i + k] == substr[j][k]) {
                k++;
            }
            if (k == strlen(substr[j])) {
                cover += strlen(substr[j]);
                i += k - 1;
                break;
            } else {
                i++;
            }
            j++;
        }
        if (cover > 0) {
            min_cover = cover;
            break;
        }
    }
    return min_cover;
}

int max_coverage(char *A, int N, char substr[MAX_SUBSTR][MAX_LEN]) {
    int len = strlen(A);
    int max_cover = 0;
    for (int i = 0; i <= len - N; i++) {
        int cover = 0;
        int j = 0;
        while (j < N) {
            int k = 0;
            while (k < strlen(substr[j]) && A[i + k] == substr[j][k]) {
                k++;
            }
            if (k == strlen(substr[j])) {
                cover += strlen(substr[j]);
                i += k - 1;
                break;
            } else {
                i++;
            }
            j++;
        }
        if (cover > 0) {
            max_cover = cover;
            break;
        }
    }
    return max_cover;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char A[MAX_LEN];
        int N;
        scanf("%s %d", A, &N);
        char substr[MAX_SUBSTR][MAX_LEN];
        for (int i = 0; i < N; i++) {
            scanf("%s", substr[i]);
        }
        int minans = min_coverage(A, N, substr);
        int maxans = max_coverage(A, N, substr);
        printf("%d %d\n", minans, maxans);
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 10001
#define MAX_N 5

char A[MAX_LEN];
char B[MAX_N][MAX_LEN];
int N;
bool covered[MAX_LEN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    scanf("%s", A);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", B[i]);
    }

    int len_A = strlen(A);
    int min_cover = len_A, max_cover = 0;

    // Calculate minimum coverage
    for (int i = 0; i < N; i++) {
        int len_B = strlen(B[i]);
        for (int j = 0; j <= len_A - len_B; j++) {
            if (strncmp(A + j, B[i], len_B) == 0) {
                min_cover = min(min_cover, len_B);
                break;
            }
        }
    }

    // Calculate maximum coverage
    memset(covered, 0, sizeof(covered));
    for (int i = 0; i < N; i++) {
        int len_B = strlen(B[i]);
        for (int j = 0; j <= len_A - len_B; j++) {
            if (strncmp(A + j, B[i], len_B) == 0) {
                for (int k = 0; k < len_B; k++) {
                    covered[j + k] = true;
                }
            }
        }
    }

    for (int i = 0; i < len_A; i++) {
        if (covered[i]) {
            max_cover++;
        }
    }

    printf("%d %d\n", min_cover, max_cover);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
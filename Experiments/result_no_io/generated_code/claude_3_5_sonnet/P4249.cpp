#include <stdio.h>
#include <string.h>

#define MAX_N 100

int N;
int matrix[MAX_N][MAX_N];
int result[MAX_N][MAX_N];

int count_rps() {
    int count = 0;
    for (int i = 0; i < N - 2; i++) {
        for (int j = i + 1; j < N - 1; j++) {
            for (int k = j + 1; k < N; k++) {
                if ((result[i][j] && result[j][k] && result[k][i]) ||
                    (result[j][i] && result[i][k] && result[k][j]) ||
                    (result[i][k] && result[k][j] && result[j][i])) {
                    count++;
                }
            }
        }
    }
    return count;
}

void solve() {
    memcpy(result, matrix, sizeof(matrix));
    
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (result[i][j] == 2) {
                result[i][j] = 1;
                result[j][i] = 0;
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    solve();
    
    int rps_count = count_rps();
    printf("%d\n", rps_count);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
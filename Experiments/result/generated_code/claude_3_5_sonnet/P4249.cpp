#include <stdio.h>
#include <string.h>

#define MAX_N 100

int N;
int matrix[MAX_N][MAX_N];
int result[MAX_N][MAX_N];

int count_scissors_rock_paper() {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if ((result[i][j] && result[j][k] && result[k][i]) ||
                    (result[j][i] && result[k][j] && result[i][k])) {
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
            if (matrix[i][j] == 2 && matrix[j][i] == 2) {
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
    
    int max_count = count_scissors_rock_paper();
    printf("%d\n", max_count);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
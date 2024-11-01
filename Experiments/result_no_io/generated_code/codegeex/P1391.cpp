#include <stdio.h>
#include <stdlib.h>

#define MAXN 18

int n;
int matrix[MAXN][MAXN];
int modified[MAXN][MAXN];

int countModified() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (modified[i][j] != matrix[i][j]) {
                count++;
            }
        }
    }
    return count;
}

int isValid() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int count = 0;
            if (i > 0 && matrix[i-1][j] == 1) count++;
            if (i < n-1 && matrix[i+1][j] == 1) count++;
            if (j > 0 && matrix[i][j-1] == 1) count++;
            if (j < n-1 && matrix[i][j+1] == 1) count++;
            if (count % 2 != 0) return 0;
        }
    }
    return 1;
}

int solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            modified[i][j] = matrix[i][j];
        }
    }
    int minModified = n * n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (modified[i][j] == 0) {
                modified[i][j] = 1;
                int modifiedCount = countModified();
                if (modifiedCount < minModified) {
                    if (isValid()) {
                        minModified = modifiedCount;
                    }
                }
                modified[i][j] = 0;
            }
        }
    }
    return minModified;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int result = solve();
    if (result == n * n) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}
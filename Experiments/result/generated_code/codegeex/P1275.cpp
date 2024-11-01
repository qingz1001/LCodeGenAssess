#include <stdio.h>
#include <stdbool.h>

bool checkEqual(int n, int m, int arr1[n][m], int arr2[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr1[i][j] != arr2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool isTransformable(int n, int m, int arr1[n][m], int arr2[n][m]) {
    // Check if the number of 1s in each row is the same
    int rowSum1[n], rowSum2[n];
    for (int i = 0; i < n; i++) {
        rowSum1[i] = 0;
        rowSum2[i] = 0;
        for (int j = 0; j < m; j++) {
            rowSum1[i] += arr1[i][j];
            rowSum2[i] += arr2[i][j];
        }
        if (rowSum1[i] != rowSum2[i]) {
            return false;
        }
    }

    // Check if the number of 1s in each column is the same
    int colSum1[m], colSum2[m];
    for (int j = 0; j < m; j++) {
        colSum1[j] = 0;
        colSum2[j] = 0;
        for (int i = 0; i < n; i++) {
            colSum1[j] += arr1[i][j];
            colSum2[j] += arr2[i][j];
        }
        if (colSum1[j] != colSum2[j]) {
            return false;
        }
    }

    // Check if the columns can be rearranged to match the second board
    for (int i = 0; i < n; i++) {
        int temp[m];
        for (int j = 0; j < m; j++) {
            temp[j] = arr1[i][j];
        }
        for (int j = 0; j < m; j++) {
            arr1[i][j] = temp[colSum1[j]];
        }
    }

    return checkEqual(n, m, arr1, arr2);
}

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int arr1[n][m], arr2[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &arr1[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &arr2[i][j]);
            }
        }
        if (isTransformable(n, m, arr1, arr2)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
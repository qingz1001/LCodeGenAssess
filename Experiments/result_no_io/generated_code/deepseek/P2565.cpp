#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int total_faces = n * m;
    int dice[n][m];
    int used[total_faces + 1];
    for (int i = 0; i <= total_faces; i++) {
        used[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int target = a[i] - 1;
        int count = 0;
        for (int j = 1; j <= total_faces; j++) {
            if (!used[j]) {
                dice[target][count] = j;
                used[j] = 1;
                count++;
                if (count == m) break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", dice[i][j]);
            if (j < m - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
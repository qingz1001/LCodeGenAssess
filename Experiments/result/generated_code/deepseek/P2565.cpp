#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Check if there is a solution
    for (int i = 0; i < n; i++) {
        if (a[a[i] - 1] != a[i]) {
            printf("0\n");
            return 0;
        }
    }

    // Generate the dice faces
    int dice[n][m];
    int num = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dice[i][j] = num++;
        }
    }

    // Output the dice faces
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", dice[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
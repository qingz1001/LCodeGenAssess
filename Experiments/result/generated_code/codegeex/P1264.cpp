#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int w[n], d[n], a[n][n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &d[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        int max_score = w[i] + d[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                max_score += a[i][j];
            }
        }
        int is_champion = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int other_score = w[j] + d[j];
                for (int k = 0; k < n; k++) {
                    if (j != k) {
                        other_score += a[j][k];
                    }
                }
                if (other_score >= max_score) {
                    is_champion = 0;
                    break;
                }
            }
        }
        if (is_champion) {
            printf("%d ", i + 1);
        }
    }
    return 0;
}
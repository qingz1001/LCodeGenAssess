#include <stdio.h>
#include <stdlib.h>

#define MAX_N 26

int main() {
    int n;
    scanf("%d", &n);
    
    int w[MAX_N], d[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &w[i], &d[i]);
    }
    
    int a[MAX_N][MAX_N];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    
    int max_points = 0;
    for (int i = 0; i < n; ++i) {
        int points = w[i] + d[i];
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                points += w[j] + d[j];
            }
        }
        if (points > max_points) {
            max_points = points;
        }
    }
    
    printf("Possible champions: ");
    for (int i = 0; i < n; ++i) {
        int points = w[i] + d[i];
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                points += w[j] + d[j];
            }
        }
        if (points == max_points) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    
    return 0;
}
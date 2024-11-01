#include <stdio.h>
#include <stdlib.h>

#define MAXN 25

int main() {
    int n;
    scanf("%d", &n);

    int wins[MAXN], draws[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &wins[i], &draws[i]);
    }

    int remaining_matches[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &remaining_matches[i][j]);
        }
    }

    int max_possible_wins[MAXN];
    for (int i = 0; i < n; i++) {
        max_possible_wins[i] = wins[i];
        for (int j = 0; j < n; j++) {
            max_possible_wins[i] += remaining_matches[i][j];
        }
    }

    int max_wins = 0;
    for (int i = 0; i < n; i++) {
        if (max_possible_wins[i] > max_wins) {
            max_wins = max_possible_wins[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (max_possible_wins[i] == max_wins) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    return 0;
}
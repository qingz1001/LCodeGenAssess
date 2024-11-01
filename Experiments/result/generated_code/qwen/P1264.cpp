#include <stdio.h>
#include <stdlib.h>

#define MAX_N 26

int n;
int w[MAX_N], d[MAX_N];
int a[MAX_N][MAX_N];

void dfs(int team, int max_wins, int current_wins) {
    if (current_wins > max_wins) return;
    if (team == n) {
        if (current_wins == max_wins) {
            for (int i = 0; i < n; i++) {
                if (w[i] + current_wins == max_wins) {
                    printf("%d ", i + 1);
                }
            }
            printf("\n");
        }
        return;
    }

    for (int other = 0; other < n; other++) {
        if (other != team && a[team][other] > 0) {
            a[team][other]--;
            a[other][team]--;
            dfs(other, max_wins, current_wins + 1);
            a[team][other]++;
            a[other][team]++;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &d[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int max_wins = 0;
    for (int i = 0; i < n; i++) {
        max_wins = (max_wins > w[i]) ? max_wins : w[i];
    }

    dfs(0, max_wins, w[0]);

    return 0;
}
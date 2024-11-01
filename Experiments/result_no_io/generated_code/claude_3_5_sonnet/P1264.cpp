#include <stdio.h>
#include <string.h>

#define MAX_N 25

int n;
int w[MAX_N], d[MAX_N], a[MAX_N][MAX_N];
int max_wins = 0;
int can_win[MAX_N];

void dfs(int team1, int team2, int wins[]) {
    if (team1 == n) {
        for (int i = 0; i < n; i++) {
            if (wins[i] > max_wins) {
                max_wins = wins[i];
                memset(can_win, 0, sizeof(can_win));
                can_win[i] = 1;
            } else if (wins[i] == max_wins) {
                can_win[i] = 1;
            }
        }
        return;
    }
    
    if (team2 == n) {
        dfs(team1 + 1, team1 + 2, wins);
        return;
    }
    
    for (int i = 0; i <= a[team1][team2]; i++) {
        wins[team1] += i;
        wins[team2] += a[team1][team2] - i;
        dfs(team1, team2 + 1, wins);
        wins[team1] -= i;
        wins[team2] -= a[team1][team2] - i;
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
    
    int wins[MAX_N];
    for (int i = 0; i < n; i++) {
        wins[i] = w[i];
    }
    
    dfs(0, 1, wins);
    
    for (int i = 0; i < n; i++) {
        if (can_win[i]) {
            printf("%d ", i + 1);
        }
    }
    
    return 0;
}
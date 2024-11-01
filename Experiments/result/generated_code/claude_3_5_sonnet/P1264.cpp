#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 25

int n;
int w[MAX_N], d[MAX_N];
int a[MAX_N][MAX_N];
int max_wins;
bool can_win[MAX_N];

void dfs(int curr_team, int curr_match, int wins[]) {
    if (curr_team == n) {
        int max_win = 0;
        for (int i = 0; i < n; i++) {
            if (wins[i] > max_win) {
                max_win = wins[i];
            }
        }
        if (max_win > max_wins) {
            max_wins = max_win;
            memset(can_win, false, sizeof(can_win));
        }
        if (max_win == max_wins) {
            for (int i = 0; i < n; i++) {
                if (wins[i] == max_win) {
                    can_win[i] = true;
                }
            }
        }
        return;
    }
    
    if (curr_match == n) {
        dfs(curr_team + 1, curr_team + 2, wins);
        return;
    }
    
    if (curr_match == curr_team) {
        dfs(curr_team, curr_match + 1, wins);
        return;
    }
    
    for (int i = 0; i < a[curr_team][curr_match]; i++) {
        wins[curr_team]++;
        dfs(curr_team, curr_match + 1, wins);
        wins[curr_team]--;
        
        wins[curr_match]++;
        dfs(curr_team, curr_match + 1, wins);
        wins[curr_match]--;
    }
    
    dfs(curr_team, curr_match + 1, wins);
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
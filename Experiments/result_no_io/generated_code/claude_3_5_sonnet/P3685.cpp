#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10
#define MAX_LEN 100000

int n;
int hints[MAX_N][10];
int hint_len[MAX_N];
bool used[10];
int sequence[MAX_LEN];
int min_len = MAX_LEN;

bool check_hint(int start, int end, int hint_index) {
    int idx = 0;
    for (int i = start; i != end && idx < hint_len[hint_index]; i = (i + 1) % min_len) {
        if (sequence[i] == hints[hint_index][idx]) {
            idx++;
        }
    }
    return idx == hint_len[hint_index];
}

bool check_all_hints() {
    for (int i = 0; i < n; i++) {
        bool valid = false;
        for (int start = 0; start < min_len && !valid; start++) {
            if (check_hint(start, start, i) || check_hint(start, (start - 1 + min_len) % min_len, i)) {
                valid = true;
            }
        }
        if (!valid) return false;
    }
    return true;
}

void dfs(int pos) {
    if (pos == min_len) {
        if (check_all_hints()) {
            printf("%d\n", min_len);
            exit(0);
        }
        return;
    }
    
    for (int i = 1; i <= 9; i++) {
        if (!used[i]) {
            used[i] = true;
            sequence[pos] = i;
            dfs(pos + 1);
            used[i] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int num;
        while (scanf("%d", &num) && num != 0) {
            hints[i][hint_len[i]++] = num;
        }
    }
    
    for (min_len = 1; min_len <= 9; min_len++) {
        memset(used, 0, sizeof(used));
        dfs(0);
    }
    
    printf("-1\n");
    return 0;
}
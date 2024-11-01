#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10
#define MAX_LEN 100

int n;
int hints[MAX_N][10];
int hint_len[MAX_N];
bool used[10];
int sequence[MAX_LEN];
int min_len = MAX_LEN;

bool check_hint(int start, int end, int hint_index) {
    int i = start, j = 0;
    bool found[10] = {false};
    while (i != end) {
        if (!found[sequence[i]]) {
            if (sequence[i] != hints[hint_index][j]) return false;
            found[sequence[i]] = true;
            j++;
        }
        i = (i + 1) % min_len;
    }
    return j == hint_len[hint_index];
}

bool check_all_hints() {
    for (int i = 0; i < n; i++) {
        bool valid = false;
        for (int j = 0; j < min_len; j++) {
            if (check_hint(j, (j - 1 + min_len) % min_len, i) || 
                check_hint((j - 1 + min_len) % min_len, j, i)) {
                valid = true;
                break;
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
    
    for (min_len = 1; min_len < MAX_LEN; min_len++) {
        memset(used, 0, sizeof(used));
        dfs(0);
    }
    
    printf("-1\n");
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_LEN 20
#define MAX_TOTAL_LEN 400

char codes[MAX_N][MAX_LEN + 1];
int n, total_len;
char result[MAX_TOTAL_LEN + 1];
bool used[MAX_N];
int best_len = MAX_TOTAL_LEN;
char best_result[MAX_TOTAL_LEN + 1];

bool dfs(int pos, int count) {
    if (count > 1) {
        if (pos < best_len || (pos == best_len && strcmp(result, best_result) < 0)) {
            best_len = pos;
            strcpy(best_result, result);
        }
        return true;
    }
    
    if (pos >= total_len) return false;
    
    bool found = false;
    for (int i = 0; i < n; i++) {
        int len = strlen(codes[i]);
        if (pos + len <= total_len && strncmp(result + pos, codes[i], len) == 0) {
            if (!used[i]) {
                used[i] = true;
                found |= dfs(pos + len, count + 1);
                used[i] = false;
            } else {
                found |= dfs(pos + len, count);
            }
        }
    }
    return found;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", codes[i]);
        total_len += strlen(codes[i]);
    }
    
    for (int i = 0; i < n; i++) {
        strcpy(result, codes[i]);
        used[i] = true;
        dfs(strlen(codes[i]), 1);
        used[i] = false;
    }
    
    printf("%d\n%s\n", best_len, best_result);
    return 0;
}
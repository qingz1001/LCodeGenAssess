#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_LEN 21
#define MAX_T_LEN 401

char codes[MAX_N][MAX_LEN];
int n, min_len = MAX_T_LEN;
char min_t[MAX_T_LEN];
bool used[MAX_N];

void dfs(char *t, int len, int count) {
    if (count >= 2 && len <= min_len) {
        if (len < min_len || strcmp(t, min_t) < 0) {
            min_len = len;
            strcpy(min_t, t);
        }
        return;
    }
    
    if (len >= min_len) return;
    
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            int code_len = strlen(codes[i]);
            strcat(t, codes[i]);
            used[i] = true;
            dfs(t, len + code_len, count + 1);
            used[i] = false;
            t[len] = '\0';
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", codes[i]);
    }
    
    char t[MAX_T_LEN] = "";
    dfs(t, 0, 0);
    
    printf("%d\n%s\n", min_len, min_t);
    
    return 0;
}
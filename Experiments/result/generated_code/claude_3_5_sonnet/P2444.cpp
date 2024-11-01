#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 2000
#define MAX_LEN 30000

char virus[MAX_N][MAX_LEN];
int len[MAX_N];
int n;

bool dfs(int depth, char* prefix) {
    if (depth == 20) return true;
    
    for (int i = 0; i < 2; i++) {
        prefix[depth] = i + '0';
        prefix[depth + 1] = '\0';
        
        bool safe = true;
        for (int j = 0; j < n; j++) {
            if (strstr(prefix, virus[j]) != NULL) {
                safe = false;
                break;
            }
        }
        
        if (safe && dfs(depth + 1, prefix)) {
            return true;
        }
    }
    
    return false;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", virus[i]);
        len[i] = strlen(virus[i]);
    }
    
    char prefix[21] = "";
    if (dfs(0, prefix)) {
        printf("TAK\n");
    } else {
        printf("NIE\n");
    }
    
    return 0;
}
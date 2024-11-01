#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 2000
#define MAX_LEN 15

char virus[MAX_N][MAX_LEN + 1];
int n;

bool dfs(char* code, int len) {
    if (len > 10) return true;
    
    for (int i = 0; i < 2; i++) {
        code[len] = i + '0';
        code[len + 1] = '\0';
        
        bool safe = true;
        for (int j = 0; j < n && safe; j++) {
            if (strstr(code, virus[j]) != NULL) {
                safe = false;
            }
        }
        
        if (safe && dfs(code, len + 1)) {
            return true;
        }
    }
    
    return false;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", virus[i]);
    }
    
    char code[20] = "";
    if (dfs(code, 0)) {
        printf("TAK\n");
    } else {
        printf("NIE\n");
    }
    
    return 0;
}
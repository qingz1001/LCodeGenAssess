#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_S 500005
#define MAX_T 500005

char S[MAX_S];
int nxt[MAX_S][26];
int fail[MAX_T];

void build_nxt(int n) {
    for (int i = 0; i < 26; i++) nxt[n][i] = n + 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) 
            nxt[i][j] = nxt[i+1][j];
        nxt[i][S[i]-'a'] = i + 1;
    }
}

void build_fail(char *T, int m) {
    fail[0] = fail[1] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j && T[i] != T[j]) j = fail[j];
        if (T[i] == T[j]) j++;
        fail[i+1] = j;
    }
}

int count_valid(char *T, int m, int l, int r) {
    int cnt = 0;
    for (int i = 0, j = l; i <= m; i++) {
        while (j <= r && S[j-1] != T[i]) j = nxt[j][T[i]-'a'];
        if (j > r) {
            cnt += m - i;
            break;
        }
        j++;
    }
    return cnt;
}

int main() {
    scanf("%s", S);
    int n = strlen(S);
    build_nxt(n);
    
    int Q;
    scanf("%d", &Q);
    
    char T[MAX_T];
    int l, r;
    
    while (Q--) {
        scanf("%s %d %d", T, &l, &r);
        int m = strlen(T);
        build_fail(T, m);
        
        int total = (m + 1) * m / 2;
        int invalid = count_valid(T, m, l, r);
        
        printf("%d\n", total - invalid);
    }
    
    return 0;
}
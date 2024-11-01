#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 998244353
#define MAXN 400005

char s[MAXN];
int n, m;
int stack[MAXN], top;
int L[MAXN], R[MAXN];
int f[MAXN][2], g[MAXN][2];

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int mul(int a, int b) {
    return (long long)a * b % MOD;
}

void calc(int x) {
    if (s[x] == '0') {
        f[x][0] = 1;
        f[x][1] = 0;
    } else if (s[x] == '1') {
        f[x][0] = 0;
        f[x][1] = 1;
    } else if (s[x] >= 'a' && s[x] <= 'z') {
        f[x][0] = f[x][1] = 1;
    } else if (s[x] == '&') {
        f[x][0] = add(mul(f[L[x]][0], f[R[x]][0]), mul(f[L[x]][0], f[R[x]][1]));
        f[x][0] = add(f[x][0], mul(f[L[x]][1], f[R[x]][0]));
        f[x][1] = mul(f[L[x]][1], f[R[x]][1]);
    } else if (s[x] == '|') {
        f[x][0] = mul(f[L[x]][0], f[R[x]][0]);
        f[x][1] = add(mul(f[L[x]][0], f[R[x]][1]), mul(f[L[x]][1], f[R[x]][0]));
        f[x][1] = add(f[x][1], mul(f[L[x]][1], f[R[x]][1]));
    } else if (s[x] == '^') {
        f[x][0] = add(mul(f[L[x]][0], f[R[x]][0]), mul(f[L[x]][1], f[R[x]][1]));
        f[x][1] = add(mul(f[L[x]][0], f[R[x]][1]), mul(f[L[x]][1], f[R[x]][0]));
    }
}

void dfs(int x) {
    if (L[x]) dfs(L[x]);
    if (R[x]) dfs(R[x]);
    calc(x);
}

int main() {
    scanf("%d", &m);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else if (s[i] == ')') {
            L[i] = stack[top--] + 1;
            R[L[i] - 2] = i - 1;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (s[i] == '&' || s[i] == '|' || s[i] == '^') {
            if (!L[i]) L[i] = i - 1;
            if (!R[i]) R[i] = i + 1;
        }
    }
    
    dfs(1);
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = add(ans, f[i][1]);
    }
    
    printf("%d\n", ans);
    
    while (m--) {
        int pos;
        char ch;
        scanf("%d %c", &pos, &ch);
        s[pos] = ch;
        
        for (int i = pos; i; i = L[i] - 2) {
            calc(i);
        }
        
        ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = add(ans, f[i][1]);
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_Q 300005

char s[MAX_N];
int n, q;
int next[MAX_N][10];
int prev[MAX_N][10];

void preprocess() {
    for (int i = 0; i < 10; i++) {
        next[n][i] = n + 1;
        prev[0][i] = -1;
    }
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            next[i][j] = next[i + 1][j];
        }
        next[i][s[i] - '0'] = i + 1;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            prev[i][j] = prev[i - 1][j];
        }
        prev[i][s[i - 1] - '0'] = i - 1;
    }
}

long long query(int l, int r) {
    long long ans = 0;
    int len = r - l + 1;
    
    for (int i = 0; i < n - len + 1; i++) {
        int j = i + len - 1;
        if (j >= n) break;
        
        int pos = i;
        int flag = 1;
        for (int k = l - 1; k < r; k++) {
            pos = next[pos][s[k] - '0'];
            if (pos > j) {
                flag = 0;
                break;
            }
        }
        
        if (flag) {
            int left = i == 0 ? 0 : i - 1;
            int right = j == n - 1 ? n : j + 2;
            ans += (long long)(left + 1) * (n - right + 1);
        }
    }
    
    return ans;
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s);
    
    preprocess();
    
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%lld\n", query(l, r));
    }
    
    return 0;
}
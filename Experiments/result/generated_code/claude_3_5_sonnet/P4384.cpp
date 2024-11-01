#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_Q 300005

typedef long long ll;

char s[MAX_N];
int n, q;
int nxt[MAX_N][10], pre[MAX_N][10];
int last[10];

void preprocess() {
    memset(last, -1, sizeof(last));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            pre[i][j] = last[j];
        }
        last[s[i] - '0'] = i;
    }
    
    memset(last, -1, sizeof(last));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            nxt[i][j] = last[j];
        }
        last[s[i] - '0'] = i;
    }
}

ll solve(int l, int r) {
    ll ans = 0;
    int len = r - l + 1;
    
    for (int i = 0; i < n - len + 1; i++) {
        int j = i + len - 1;
        if (j >= n) break;
        
        int left = (i == 0) ? -1 : pre[i-1][s[l] - '0'];
        int right = (j == n-1) ? n : nxt[j+1][s[r] - '0'];
        
        if (memcmp(s + i, s + l, len) == 0) {
            ans += (ll)(i - left) * (right - j);
        }
    }
    
    return ans;
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s);
    
    preprocess();
    
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;
        printf("%lld\n", solve(l, r));
    }
    
    return 0;
}
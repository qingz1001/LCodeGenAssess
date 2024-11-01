#include <stdio.h>
#include <string.h>

#define MAXN 500

int n, p;
int f[2][MAXN][MAXN];
int prime[MAXN];
int cnt, vis[MAXN];

void init() {
    vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[cnt++] = i;
            for (int j = i + i; j <= n; j += i) {
                vis[j] = 1;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    init();

    int cur = 0;
    f[cur][0][0] = 1;

    for (int i = 2; i <= n; i++) {
        int num = i;
        cur ^= 1;
        memset(f[cur], 0, sizeof(f[cur]));

        for (int j = 0; j < cnt; j++) {
            if (num % prime[j] == 0) {
                int t = 0;
                while (num % prime[j] == 0) {
                    t++;
                    num /= prime[j];
                }
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l < i; l++) {
                        if (k % prime[j] == 0) {
                            f[cur][k][l] = (f[cur][k][l] + f[cur ^ 1][k][l]) % p;
                        }
                        if (l % prime[j] == 0) {
                            f[cur][k][l] = (f[cur][k][l] + f[cur ^ 1][k][l]) % p;
                        }
                        if (k % prime[j] != 0 && l % prime[j] != 0) {
                            f[cur][k + t * prime[j]][l] = (f[cur][k + t * prime[j]][l] + f[cur ^ 1][k][l]) % p;
                        }
                    }
                }
            }
        }

        if (num > 1) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < i; k++) {
                    f[cur][j + 1][k] = (f[cur][j + 1][k] + f[cur ^ 1][j][k]) % p;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) {
                continue;
            }
            ans = (ans + f[cur ^ 1][i][j]) % p;
        }
    }

    printf("%d\n", ans);
    return 0;
}
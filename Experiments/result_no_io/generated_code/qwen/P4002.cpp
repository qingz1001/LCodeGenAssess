#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const int MAXN = 30005;

int n, m;
int a[MAXN];
long long dp[MAXN][MAXN];

void add(long long &x, long long y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

void mul(long long &x, long long y) {
    x = (long long)x * y % MOD;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= j; ++k) {
                int l = j - k;
                mul(dp[i][j], dp[l][k]);
                mul(dp[i][j], a[i]);
                add(dp[i][j], dp[i - 1][l - 1]);
            }
        }
    }

    long long sum = 0;
    for (int i = 0; i <= n; ++i) {
        add(sum, dp[n][i]);
    }

    long long ans = 1;
    for (int i = 1; i <= n; ++i) {
        mul(ans, sum);
    }

    cout << ans << endl;
    return 0;
}
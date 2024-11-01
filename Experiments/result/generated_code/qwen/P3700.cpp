pp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = i * j;
        }
    }

    while (m--) {
        int a, b, x, k;
        cin >> a >> b >> x >> k;

        long long sum = 0;
        for (int i = max(1, a - k); i <= min(n, a + k); ++i) {
            for (int j = max(1, b - k); j <= min(n, b + k); ++j) {
                dp[i][j] = x;
                sum += dp[i][j];
            }
        }

        cout << (sum % MOD) << endl;
    }

    return 0;
}
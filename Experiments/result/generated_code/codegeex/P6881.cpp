#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define int long long

int n, q;
int s[200005];
int t[200005], l[200005], r[200005];
int ans[200005];
vector<pair<int, int>> v[200005];

map<int, int> mp[200005];

int main() {
    scanf("%lld%lld", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &s[i]);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%lld%lld%lld", &t[i], &l[i], &r[i]);
        v[t[i]].emplace_back(l[i], r[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            s[i] = max(s[i], s[i-1]);
        }
        for (auto j : v[i]) {
            for (int k = j.first; k <= j.second; k++) {
                ans[i] += s[k];
            }
        }
    }

    for (int i = 1; i <= q; i++) {
        printf("%lld\n", ans[t[i]]);
    }

    return 0;
}
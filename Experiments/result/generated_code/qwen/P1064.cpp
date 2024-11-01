#include <stdio.h>
#include <stdlib.h>

#define MAXN 32005
#define MAXM 70

int dp[MAXN];
struct Item {
    int price, importance, master;
};

void solve(int n, int m, struct Item items[]) {
    for (int i = 0; i <= n; i++) {
        dp[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        if (items[i].master == 0) {
            for (int j = n; j >= items[i].price; j--) {
                dp[j] = fmax(dp[j], dp[j - items[i].price] + items[i].price * items[i].importance);
            }
        } else {
            int masterPrice = items[items[i].master - 1].price;
            for (int j = n; j >= masterPrice + items[i].price; j--) {
                dp[j] = fmax(dp[j], dp[j - masterPrice - items[i].price] + masterPrice * items[items[i].master - 1].importance + items[i].price * items[i].importance);
            }
        }
    }
    printf("%d\n", dp[n]);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    struct Item items[MAXM];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &items[i].price, &items[i].importance, &items[i].master);
    }
    solve(n, m, items);
    return 0;
}
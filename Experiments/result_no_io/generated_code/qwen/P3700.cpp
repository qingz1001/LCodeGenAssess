#include <stdio.h>
#define MOD 1000000007

typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void update(ll *arr, int n, int a, int b, ll x) {
    arr[a - 1] = x / gcd(x, arr[a - 1]);
    for (int i = a; i <= n; i++) {
        arr[i - 1] *= (i + b - a);
        arr[i - 1] /= gcd(arr[i - 1], arr[i - 2]);
    }
}

ll query(ll *arr, int k) {
    ll sum = 0;
    for (int i = 0; i < k; i++) {
        sum += arr[i];
        sum %= MOD;
    }
    return sum;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    ll arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    while (m--) {
        int a, b, x, k;
        scanf("%d %d %lld %d", &a, &b, &x, &k);
        update(arr, n, a, b, x);
        printf("%lld\n", query(arr, k));
    }

    return 0;
}
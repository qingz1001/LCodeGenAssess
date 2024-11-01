#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 205

typedef long long ll;

ll b[MAXN];
ll a[MAXN];

void reverse_operation(ll *arr, int type, int x, int y) {
    if (type == 1) {
        arr[x] -= arr[y];
    } else if (type == 2) {
        arr[x] /= arr[y];
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }

    for (int i = 1; i <= m; i++) {
        int k, x, y;
        scanf("%d %d %d", &k, &x, &y);
        reverse_operation(b, k, x, y);
    }

    for (int i = 1; i <= n; i++) {
        a[i] = b[i];
    }

    for (int i = 1; i <= m; i++) {
        int k, x, y;
        scanf("%d %d %d", &k, &x, &y);
        reverse_operation(a, k, x, y);
    }

    for (int i = 1; i <= n; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");

    return 0;
}
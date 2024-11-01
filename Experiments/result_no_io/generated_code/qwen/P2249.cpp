#include <stdio.h>

#define MAXN 1000000
#define MAXM 100000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int a[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    int q[MAXM];
    for (int i = 0; i < m; ++i) {
        scanf("%d", &q[i]);
    }

    for (int i = 0; i < m; ++i) {
        int left = 0, right = n - 1, pos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (a[mid] == q[i]) {
                pos = mid + 1;
                right = mid - 1;
            } else if (a[mid] < q[i]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        printf("%d ", pos);
    }

    return 0;
}
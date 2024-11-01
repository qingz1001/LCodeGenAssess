#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
int n, a[MAXN], b[MAXN], pos[MAXN], ans = 0x3f3f3f3f;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
        pos[i] = b[i] - a[i];
        if (pos[i] < 0) pos[i] += 2 * n;
    }

    sort(pos + 1, pos + n + 1);

    for (int i = 1; i <= n; i++) {
        int j = i;
        while (pos[j] == pos[j + 1] && j < n) j++;
        ans = min(ans, j - i + 1);
        i = j;
    }

    printf("%d", ans);
    return 0;
}
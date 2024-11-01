#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005

int main() {
    int n;
    scanf("%d", &n);
    int a[MAXN][2];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a[i][0], &a[i][1]);
    }

    int visited[MAXN] = {0};
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int count = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = 1;
                j = (j + 1) % n;
                count++;
            }
            if (count != 2) {
                printf("-1\n");
                return 0;
            }
            ans += count;
        }
    }

    printf("%d\n", ans);

    return 0;
}
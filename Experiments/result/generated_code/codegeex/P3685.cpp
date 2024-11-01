#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10
#define MAXLEN 1000
#define INF 0x3f3f3f3f

int n;
int len;
int vis[10];
int ans[MAXLEN];

int main() {
    scanf("%d", &n);
    memset(vis, 0, sizeof(vis));
    int max_len = 0;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        while (x != 0) {
            vis[x]++;
            max_len = fmax(max_len, vis[x]);
            scanf("%d", &x);
        }
    }

    len = max_len;
    for (int i = 1; i <= 9; i++) {
        if (vis[i] == 0) {
            len++;
            ans[0] = i;
        }
    }

    if (len > 9) {
        printf("-1\n");
        return 0;
    }

    for (int i = 1; i < len; i++) {
        if (i % 2 == 1) {
            for (int j = 1; j <= 9; j++) {
                if (vis[j] < len && vis[j] > i / 2) {
                    ans[i] = j;
                    vis[j]++;
                    break;
                }
            }
        } else {
            for (int j = 9; j >= 1; j--) {
                if (vis[j] < len && vis[j] > i / 2) {
                    ans[i] = j;
                    vis[j]++;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <string.h>

int main() {
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int lines[45][45] = {0};
        for (int i = 0; i < n; i++) {
            int line;
            scanf("%d", &line);
            for (int j = 0; j < i; j++) {
                if (lines[line][j] == 0) {
                    lines[line][j] = 1;
                    lines[j][line] = 1;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int count = 0;
                for (int k = 0; k < n; k++) {
                    if (lines[i][k] && lines[j][k]) {
                        count++;
                    }
                }
                if (count == 2) {
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
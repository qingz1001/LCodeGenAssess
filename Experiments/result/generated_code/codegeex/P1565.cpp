#include <stdio.h>
#include <limits.h>

#define MAXN 201

int n, m;
int a[MAXN][MAXN];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int max_area = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int min_height = INT_MAX;
            for (int x = 1; x <= n; x++) {
                for (int y = 1; y <= m; y++) {
                    min_height = (a[x][y] < min_height) ? a[x][y] : min_height;
                }
            }
            int area = 0;
            for (int x = 1; x <= n; x++) {
                for (int y = 1; y <= m; y++) {
                    if (a[x][y] >= min_height) {
                        area++;
                    }
                }
            }
            max_area = (area > max_area) ? area : max_area;
        }
    }

    printf("%d\n", max_area);
    return 0;
}
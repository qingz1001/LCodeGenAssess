#include <stdio.h>
#include <string.h>

#define MAX 10001

int grid[MAX][MAX];

int main() {
    int n, x1, y1, x2, y2;
    scanf("%d", &n);

    memset(grid, 0, sizeof(grid));

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x1 > x2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        if (y1 > y2) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int x = x1; x < x2; x++) {
            grid[x][y1]++;
            grid[x][y2]--;
        }
    }

    long long area = 0;
    for (int x = 0; x < MAX; x++) {
        int count = 0;
        for (int y = 0; y < MAX; y++) {
            count += grid[x][y];
            if (count > 0) {
                area++;
            }
        }
    }

    printf("%lld\n", area);

    return 0;
}
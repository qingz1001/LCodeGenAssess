#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 501
#define INF 1e18

typedef long long ll;

int n;
ll flow[MAX_N + 1][MAX_N + 1][4];
double height[MAX_N + 1][MAX_N + 1];

void read_input() {
    scanf("%d", &n);
    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < n; j++) {
                int x = (dir % 2 == 0) ? i : j;
                int y = (dir % 2 == 0) ? j : i;
                scanf("%lld", &flow[x][y][dir]);
            }
        }
    }
}

void solve() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            height[i][j] = INF;
        }
    }
    height[0][0] = 0;
    height[n][n] = 1;

    for (int k = 0; k < 2 * n; k++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i > 0) {
                    double h = height[i][j] + (flow[i-1][j][2] - flow[i-1][j][0]) / (double)(flow[i-1][j][0] + flow[i-1][j][2]);
                    if (h < height[i-1][j]) height[i-1][j] = h;
                }
                if (j > 0) {
                    double h = height[i][j] + (flow[i][j-1][3] - flow[i][j-1][1]) / (double)(flow[i][j-1][1] + flow[i][j-1][3]);
                    if (h < height[i][j-1]) height[i][j-1] = h;
                }
                if (i < n) {
                    double h = height[i][j] + (flow[i][j][0] - flow[i][j][2]) / (double)(flow[i][j][0] + flow[i][j][2]);
                    if (h < height[i+1][j]) height[i+1][j] = h;
                }
                if (j < n) {
                    double h = height[i][j] + (flow[i][j][1] - flow[i][j][3]) / (double)(flow[i][j][1] + flow[i][j][3]);
                    if (h < height[i][j+1]) height[i][j+1] = h;
                }
            }
        }
    }

    double total_energy = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            double dh = height[i][j+1] - height[i][j];
            total_energy += flow[i][j][1] * (dh > 0 ? dh : 0);
            total_energy += flow[i][j][3] * (-dh > 0 ? -dh : 0);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            double dh = height[i+1][j] - height[i][j];
            total_energy += flow[i][j][0] * (dh > 0 ? dh : 0);
            total_energy += flow[i][j][2] * (-dh > 0 ? -dh : 0);
        }
    }

    printf("%lld\n", (ll)(total_energy + 0.5));
}

int main() {
    read_input();
    solve();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAXN 505
#define MAXA 100005
#define MAXB 100005

int n, m, a, b;
int sources[MAXA][2];
int leaders[MAXB][2];
int infection_time[MAXN][MAXN];

void bfs() {
    int queue[MAXA * 2];
    int front = 0, rear = 0;

    for (int i = 0; i < a; i++) {
        queue[rear++] = sources[i][0] * m + sources[i][1];
        infection_time[sources[i][0]][sources[i][1]] = 0;
    }

    while (front < rear) {
        int current = queue[front++];
        int x = current / m, y = current % m;

        if (x > 0 && infection_time[x - 1][y] == -1) {
            infection_time[x - 1][y] = infection_time[x][y] + 1;
            queue[rear++] = (x - 1) * m + y;
        }
        if (x < n - 1 && infection_time[x + 1][y] == -1) {
            infection_time[x + 1][y] = infection_time[x][y] + 1;
            queue[rear++] = (x + 1) * m + y;
        }
        if (y > 0 && infection_time[x][y - 1] == -1) {
            infection_time[x][y - 1] = infection_time[x][y] + 1;
            queue[rear++] = x * m + (y - 1);
        }
        if (y < m - 1 && infection_time[x][y + 1] == -1) {
            infection_time[x][y + 1] = infection_time[x][y] + 1;
            queue[rear++] = x * m + (y + 1);
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);

    for (int i = 0; i < a; i++) {
        scanf("%d %d", &sources[i][0], &sources[i][1]);
        sources[i][0]--;
        sources[i][1]--;
    }

    for (int i = 0; i < b; i++) {
        scanf("%d %d", &leaders[i][0], &leaders[i][1]);
        leaders[i][0]--;
        leaders[i][1]--;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            infection_time[i][j] = -1;
        }
    }

    bfs();

    for (int i = 0; i < b; i++) {
        printf("%d\n", infection_time[leaders[i][0]][leaders[i][1]]);
    }

    return 0;
}